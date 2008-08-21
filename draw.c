#include <string.h>
#include <X11/Xlib.h>

#define FONT "-*-nu.de-*-*-*-*-11-*-*-*-*-*-*-*"

extern Display* dpy;
extern Window win;
extern GC gc;
extern int screen;

Font font = 0;

void
drawtext(int x, int y, unsigned long color, char* text)
{
	XSetForeground(dpy, gc, color); 
	XDrawString(dpy, win, gc, x, y, text, strlen(text));
}

void
draw()
{
	drawtext(2, 11, WhitePixel(dpy, screen), "hallo welt!");
}

void
initdrawing()
{
	font = XLoadFont(dpy, FONT);
	XSetFont(dpy, gc, font);
}
