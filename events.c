#include <stdbool.h>
#include <X11/Xlib.h>

extern Display* dpy;

extern bool running;

void
ev_expose()
{
	draw();
}

void
eventloop()
{
	XEvent ev;
	while(running && !XNextEvent(dpy, &ev)) {
		switch(ev.type) {
			case Expose:
				ev_expose();
				break;
			default:
				break;
		}
	}
}
