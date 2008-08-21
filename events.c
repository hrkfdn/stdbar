#include <errno.h>
#include <unistd.h>
#include <sys/select.h>
#include "stdbar.h"

char stext[256];

void
ev_expose()
{
	draw();
}

void
eventloop()
{
	int r, xfd = ConnectionNumber(dpy);
	XEvent ev;
	fd_set rd;
	char *p;
	char sbuf[sizeof(stext)];
	unsigned int len, offset;

	bool readin = true;
	len = sizeof stext - 1;
	sbuf[len] = stext[len] = '\0'; /* 0-terminator is never touched */
	offset = 0;
	while(running) {
		/* most of this is from dwm, thanks! */
		FD_ZERO(&rd);
		if(readin)
			FD_SET(STDIN_FILENO, &rd);
		FD_SET(xfd, &rd);
		if(select(xfd + 1, &rd, NULL, NULL, NULL) == -1) {
			if(errno == EINTR)
				continue;
			fprintf(stderr, "stdbar: select failed.\n");
			exit(EXIT_FAILURE);
		}
		if(FD_ISSET(STDIN_FILENO, &rd)) {
			switch((r = read(STDIN_FILENO, sbuf + offset, len - offset))) {
				case -1:
					strncpy(stext, strerror(errno), len);
					readin = False;
					break;
				case 0:
					strncpy(stext, "EOF", 4);
					readin = False;
					break;
				default:
					for(p = sbuf + offset; r > 0; p++, r--, offset++)
						if(*p == '\n' || *p == '\0') {
							*p = '\0';
							strncpy(stext, sbuf, len);
							p += r - 1; /* p is sbuf + offset + r - 1 */
							for(r = 0; *(p - r) && *(p - r) != '\n'; r++);
							offset = r;
							if(r)
								memmove(sbuf, p - r + 1, r);
							break;
						}
					break;
			}
		}
		draw();
		while(XPending(dpy)) {
			XNextEvent(dpy, &ev);
			switch(ev.type) {
				case Expose:
					ev_expose();
					break;
				default:
					break;
			}
		}
	}
}
