#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>

Display* dpy = 0;
Window win = 0;

int
main(int argc, char* argv[])
{
	Window root = 0;
	int screen = 0;

	if(!(dpy = XOpenDisplay(NULL))) {
			fprintf(stderr, "Could not connect to the X server.\n");
			return EXIT_FAILURE;
	}
	screen = DefaultScreen(dpy);
	root = DefaultRootWindow(dpy);

	XSetWindowAttributes attributes;
	attributes.override_redirect = 0;
	attributes.background_pixel = WhitePixel(dpy, screen);
	attributes.event_mask = ExposureMask;

	if(!(win = XCreateWindow(dpy, root, 0, 0, DisplayWidth(dpy, screen), 10, 0, DefaultDepth(dpy, screen), CopyFromParent, DefaultVisual(dpy, screen), CWOverrideRedirect | CWBackPixel | CWEventMask, &attributes))){
			fprintf(stderr, "Could not create the window.\n");
			XCloseDisplay(dpy);
			return EXIT_FAILURE;
	}
	initatoms();
	setatoms();

	XMapRaised(dpy, win);
	XSync(dpy, False);

	sleep(10);
	XCloseDisplay(dpy);
	return EXIT_SUCCESS;
}
