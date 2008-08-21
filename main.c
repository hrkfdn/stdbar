#include "stdbar.h"

bool running = true;

Display* dpy = 0;
Window win = 0;
int screen = 0;
GC gc = 0;
int barh = 0, bary = 0;

void
close()
{
	if(win) XDestroyWindow(dpy, win);
	if(gc) XFreeGC(dpy, gc);
	if(dpy) XCloseDisplay(dpy);
}

int
main(int argc, char* argv[])
{
	atexit(close);
	Window root = 0;
	loadsettings();

	if(!(dpy = XOpenDisplay(NULL))) {
			fprintf(stderr, "Could not connect to the X server.\n");
			return EXIT_FAILURE;
	}
	screen = DefaultScreen(dpy);
	root = DefaultRootWindow(dpy);
	gc = XCreateGC(dpy, root, 0, 0);

	memset(&stext, 0, sizeof(stext));
	strcpy(stext, "stdbar version "VERSION);

	XSetWindowAttributes attributes;
	attributes.override_redirect = 0;
	attributes.background_pixel = alloccolor(settings[BGCOLOR].value);
	attributes.event_mask = ExposureMask;

	initdrawing();
	
	if(!istop())
		bary = DisplayHeight(dpy, screen)-barh;

	if(!(win = XCreateWindow(dpy, root, 0, bary, DisplayWidth(dpy, screen), barh, 0, DefaultDepth(dpy, screen), CopyFromParent, DefaultVisual(dpy, screen), CWOverrideRedirect | CWBackPixel | CWEventMask, &attributes))){
			fprintf(stderr, "Could not create the window.\n");
			XCloseDisplay(dpy);
			return EXIT_FAILURE;
	}
	initatoms();
	setatoms(barh);

	draw();

	XMapRaised(dpy, win);
	XSync(dpy, False);

	eventloop();

	close();
	return EXIT_SUCCESS;
}
