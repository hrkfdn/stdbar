#ifndef _SHARED_H
#define _SHARED_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

typedef struct
{
	char* shname;
	char* value;
} setting_t;

extern setting_t settings[];

enum {
	BGCOLOR = 0, FGCOLOR, FONT, BARPOS,
};

extern Display* dpy;
extern Window win;
extern int screen;
extern GC gc;
extern int barh, bary;
extern char stext[256];
extern bool running;

#endif
