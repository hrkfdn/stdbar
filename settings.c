#include "stdbar.h"

setting_t settings[] =
{
	"BGCOLOR", "#000000",
	"FGCOLOR", "#FFFFFF",
	"FONT", "-*-fixed-*-*-*-*-12-*-*-*-*-*-*-*",
};

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
