#include <string.h>
#include <X11/Xlib.h>

extern Display* dpy;
extern Window win;
extern GC gc;
extern int screen;

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
