#include "stdbar.h"

setting_t settings[] =
{
	"BGCOLOR", "#000000",
	"FGCOLOR", "#FFFFFF",
	"FONT", "-*-fixed-*-*-*-*-12-*-*-*-*-*-*-*",
	"BARPOS", "TOP",
};

unsigned long
alloccolor(char* colorname)
{
	Colormap cmap = DefaultColormap(dpy, screen);
	XColor col;

	if(!XAllocNamedColor(dpy, cmap, colorname, &col, &col)) {
		fprintf(stderr, "Could not allocate color %s. Using white.\n", colorname);
		return XWhitePixel(dpy, screen);
	}

	return col.pixel;
}

bool
istop()
{
	switch(tolower(settings[BARPOS].value[0])) {
		case 't':
			return true;
		case 'b':
			return false;
		default:
			return true;
	}
}

void
loadsettings()
{
	char* p = 0;
	unsigned int i;

	for(i = 0; i < sizeof(settings)/sizeof(setting_t); i++) {
		setting_t* psetting = &settings[i];
		if(p = getenv(psetting->shname))
			psetting->value = p;
	}
}
