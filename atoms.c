#include "stdbar.h"

#define CREATEATOM(ident, varname) atom_t varname = { #ident, 0 }
#define INITATOM(varname) varname.atom = XInternAtom(dpy, varname.name, False)

char wmname[] = "stdbar "VERSION;

typedef struct
{
	char* name;
	Atom atom;
} atom_t;

CREATEATOM(UTF8_STRING, utf8_string);

CREATEATOM(_NET_WM_NAME, net_wm_name);
CREATEATOM(_NET_WM_WINDOW_TYPE, net_wm_window_type);
CREATEATOM(_NET_WM_WINDOW_TYPE_DOCK, net_wm_window_type_dock);
CREATEATOM(_NET_WM_STRUT, net_wm_strut);
CREATEATOM(_NET_WM_STRUT_PARTIAL, net_wm_strut_partial);

void
initatoms()
{
	INITATOM(utf8_string);

	INITATOM(net_wm_name);
	INITATOM(net_wm_window_type);
	INITATOM(net_wm_window_type_dock);
	INITATOM(net_wm_strut);
	INITATOM(net_wm_strut_partial);
}

void
setatoms(int barh)
{
	int struts[12];
	XTextProperty wname;
	XClassHint* chint;

	memset(&struts, 0, sizeof(struts));
	if(istop())
		struts[2] = barh;
	else
		struts[3] = barh;
	struts[9] = DisplayWidth(dpy, screen);

	XChangeProperty(dpy, win, net_wm_strut.atom, XA_CARDINAL, 32, PropModeReplace, (unsigned char*)struts, 4); // for compatibility reasons
	XChangeProperty(dpy, win, net_wm_strut_partial.atom, XA_CARDINAL, 32, PropModeReplace, (unsigned char*)struts, 12);
	XChangeProperty(dpy, win, net_wm_window_type.atom, XA_ATOM, 32, PropModeReplace, (unsigned char*)&net_wm_window_type_dock.atom, 1);

	XChangeProperty(dpy, win, net_wm_name.atom, utf8_string.atom, 8, PropModeReplace, (unsigned char*)wmname, strlen(wmname));
	wname.value = (unsigned char*)wmname;
	wname.encoding = XA_STRING;
	wname.format = 8;
	wname.nitems = strlen((char *) wname.value);
	XSetWMName(dpy, win, &wname);

	chint = XAllocClassHint();
	chint->res_name = "stdbar";
	chint->res_class = "stdbar";
	XSetClassHint(dpy, win, chint);
}
