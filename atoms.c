#include "stdbar.h"

#define CREATEATOM(ident, varname) atom_t varname = { #ident, 0 }
#define INITATOM(varname) varname.atom = XInternAtom(dpy, varname.name, False)

char* wmname = "stdbar "VERSION;

enum {
	STRUT_LEFT = 0, STRUT_RIGHT, STRUT_TOP, STRUT_BOTTOM,
	STRUT_LEFT_START_Y, STRUT_LEFT_END_Y, STRUT_RIGHT_START_Y, STRUT_RIGHT_END_Y,
	STRUT_TOP_START_X, STRUT_TOP_END_X, STRUT_BOTTOM_START_X, STRUT_BOTTOM_END_X
};

typedef struct
{
	char* name;
	Atom atom;
} atom_t;

CREATEATOM(UTF8_STRING, utf8_string);

CREATEATOM(_NET_WM_STATE, net_wm_state);
CREATEATOM(_NET_WM_STATE_STICKY, net_wm_state_sticky);
CREATEATOM(_NET_WM_STATE_SKIP_PAGER, net_wm_state_skip_pager);
CREATEATOM(_NET_WM_STATE_SKIP_TASKBAR, net_wm_state_skip_taskbar);

CREATEATOM(_NET_WM_NAME, net_wm_name);
CREATEATOM(_NET_WM_WINDOW_TYPE, net_wm_window_type);
CREATEATOM(_NET_WM_WINDOW_TYPE_DOCK, net_wm_window_type_dock);
CREATEATOM(_NET_WM_STRUT, net_wm_strut);
CREATEATOM(_NET_WM_STRUT_PARTIAL, net_wm_strut_partial);

CREATEATOM(_NET_WM_DESKTOP, net_wm_desktop);

void
initatoms()
{
	INITATOM(utf8_string);

	INITATOM(net_wm_state);
	INITATOM(net_wm_state_sticky);
	INITATOM(net_wm_state_skip_pager);
	INITATOM(net_wm_state_skip_taskbar);

	INITATOM(net_wm_name);
	INITATOM(net_wm_window_type);
	INITATOM(net_wm_window_type_dock);
	INITATOM(net_wm_strut);
	INITATOM(net_wm_strut_partial);

	INITATOM(net_wm_desktop);
}

void
setatoms(int barh)
{
	unsigned int desk = 0xFFFFFFFF;
	int struts[12];
	XTextProperty wname;
	XClassHint* chint;
	Atom states[3] = { net_wm_state_sticky.atom, net_wm_state_skip_pager.atom, net_wm_state_skip_taskbar.atom };
	XSizeHints* shints = 0;

	memset(&struts, 0, sizeof(struts));
	if(istop()) {
		struts[STRUT_TOP] = barh;
		struts[STRUT_TOP_END_X] = DisplayWidth(dpy, screen);
	}
	else {
		struts[STRUT_BOTTOM] = barh;
		struts[STRUT_BOTTOM_END_X] = DisplayWidth(dpy, screen);
	}

	XChangeProperty(dpy, win, net_wm_strut.atom, XA_CARDINAL, 32, PropModeReplace, (unsigned char*)struts, 4); // for compatibility reasons
	XChangeProperty(dpy, win, net_wm_strut_partial.atom, XA_CARDINAL, 32, PropModeReplace, (unsigned char*)struts, 12);
	XChangeProperty(dpy, win, net_wm_window_type.atom, XA_ATOM, 32, PropModeReplace, (unsigned char*)&net_wm_window_type_dock.atom, 1);

	XChangeProperty(dpy, win, net_wm_name.atom, utf8_string.atom, 8, PropModeReplace, (unsigned char*)wmname, strlen(wmname));
	XStringListToTextProperty(&wmname, 1, &wname);
	XSetWMName(dpy, win, &wname);

	chint = XAllocClassHint();
	chint->res_name = "stdbar";
	chint->res_class = "stdbar";
	XSetClassHint(dpy, win, chint);

	XChangeProperty(dpy, win, net_wm_state.atom, XA_ATOM, 32, PropModeReplace, (unsigned char*)&states, 3);

	shints = XAllocSizeHints();
	shints->min_width = DisplayWidth(dpy, screen);
	shints->min_height = barh;
	shints->flags = PPosition|PMinSize;
	XSetWMNormalHints(dpy, win, shints);

	XChangeProperty(dpy, win, net_wm_desktop.atom, XA_CARDINAL, 32, PropModeReplace, (unsigned char*)&desk, 1);

	XSync(dpy, False);
}
