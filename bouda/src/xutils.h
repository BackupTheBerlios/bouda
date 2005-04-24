/*
 * panel-xutils.h: X related utility methods.
 *
 * Copyright (C) 2003 Sun Microsystems, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * Authors:
 *	Mark McLoughlin <mark@skynet.ie>
 */

#ifndef __PANEL_XUTILS_H__
#define __PANEL_XUTILS_H__

#include <glib/gmacros.h>
#include <glib/gtypes.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>

#include <X11/Xlib.h>

G_BEGIN_DECLS

typedef enum {
	PANEL_XUTILS_TYPE_NORMAL,
	PANEL_XUTILS_TYPE_DOCK
} PanelXUtilsWindowType;

void xutils_set_window_type (GdkWindow             *gdk_window,
				   PanelXUtilsWindowType  type);

G_END_DECLS

#endif /* __PANEL_XUTILS_H__ */
