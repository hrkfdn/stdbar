#include "stdbar.h"

#define FONT "-*-nu.de-*-*-*-*-11-*-*-*-*-*-*-*"

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
	drawtext(2, 11, WhitePixel(dpy, screen), stext);
}

void
initdrawing()
{
	XFontStruct* fontstruct = XLoadQueryFont(dpy, FONT);
	if(fontstruct) {
		XSetFont(dpy, gc, fontstruct->fid);
		barh = fontstruct->max_bounds.ascent + fontstruct->max_bounds.descent;
	} else {
		fprintf(stderr, "Font could not be loaded! Using fixed.\n");
		barh = 11; // approximate value :( TODO: calculate height
	}
}
