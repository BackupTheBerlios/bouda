#include "xutils.h"

#include <glib.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

static Atom net_wm_window_type        = None;
static Atom net_wm_window_type_dock   = None;
static Atom net_wm_window_type_normal = None;

void
xutils_set_window_type (GdkWindow *gdk_window,	
			      PanelXUtilsWindowType  type)
{
	Display *display;
	Window   window;
	Atom     atoms [2];
	int      i = 0;

	g_return_if_fail (GDK_IS_WINDOW (gdk_window));

	display = GDK_WINDOW_XDISPLAY (gdk_window);
	window  = GDK_WINDOW_XWINDOW (gdk_window);

	if (net_wm_window_type == None)
		net_wm_window_type = XInternAtom (display,
						  "_NET_WM_WINDOW_TYPE",
						  False);

	switch (type) {
	case PANEL_XUTILS_TYPE_DOCK:
		if (net_wm_window_type_dock == None)
			net_wm_window_type_dock = XInternAtom (display,
							       "_NET_WM_WINDOW_TYPE_DOCK",
							       False);
		atoms [i++] = net_wm_window_type_dock;
		break;
	case PANEL_XUTILS_TYPE_NORMAL:
		if (net_wm_window_type_normal == None)
			net_wm_window_type_normal = XInternAtom (display,
								 "_NET_WM_WINDOW_TYPE_NORMAL",
								 False);
		atoms [i++] = net_wm_window_type_normal;
		break;
	default:
		g_assert_not_reached ();
		break;
	}

	gdk_error_trap_push ();
	XChangeProperty (display, window, net_wm_window_type,
			 XA_ATOM, 32, PropModeReplace,
			 (guchar *) &atoms, i);
	gdk_error_trap_pop ();
}
