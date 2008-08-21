#include "stdbar.h"

Font font = 0;

void
drawtext(int x, int y, unsigned long color, char* text)
{
	XClearWindow(dpy, win);
	XSetForeground(dpy, gc, color); 
	XDrawString(dpy, win, gc, x, y, text, strlen(text));
}

void
draw()
{
	drawtext(2, barh-1, alloccolor(settings[FGCOLOR].value), stext);
}

void
initdrawing()
{
	XFontStruct* fontstruct = XLoadQueryFont(dpy, settings[FONT].value);
	if(fontstruct) {
		XSetFont(dpy, gc, fontstruct->fid);
		barh = fontstruct->ascent + fontstruct->descent;
	} else {
		fprintf(stderr, "Font could not be loaded! Using fixed.\n");
		barh = 12; 
	}
	barh += 1;
}
