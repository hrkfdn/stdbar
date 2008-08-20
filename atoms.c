#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>

extern Display *dpy;
extern Window win;

#define CREATEATOM(ident, varname) atom_t varname = { #ident, 0 }
#define INITATOM(varname) varname.atom = XInternAtom(dpy, varname.name, False)

typedef struct
{
	char* name;
	Atom atom;
} atom_t;

CREATEATOM(_NET_SUPPORTED, net_supported);
CREATEATOM(_NET_WM_WINDOW_TYPE, net_wm_window_type);
CREATEATOM(_NET_WM_WINDOW_TYPE_DOCK, net_wm_window_type_dock);
CREATEATOM(_NET_WM_STRUT, net_wm_strut);
CREATEATOM(_NET_WM_STRUT_PARTIAL, net_wm_strut_partial);

void
initatoms()
{
	INITATOM(net_supported);
	INITATOM(net_wm_window_type);
	INITATOM(net_wm_window_type_dock);
	INITATOM(net_wm_strut);
	INITATOM(net_wm_strut_partial);
}

void
setatoms()
{
	XChangeProperty(dpy, win, net_wm_window_type.atom, XA_ATOM, 32, PropModeReplace, (unsigned char*)&net_wm_window_type_dock.atom, 1);
}
