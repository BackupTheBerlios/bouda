#include <glib.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

#include "bouda.h"
#include "read-icon-list.h"
#include "cairo-canvas.h"
#include "mouse-events.h"
#include "xutils.h"
#include "read-properties.h"
#include "validate-config.h"


static void bouda_set_icon_properties (B_Launcher *b_launcher);
static void bouda_set_bouda_properties (B_Window *b_window);
static void destroy (GtkWidget *widget, B_Window *b_window);
static GtkWidget *bouda_cairo_widget (B_Window *b_window);
static GtkWidget *bouda_main_widget (B_Window *b_window);


GtkWidget 
*bouda_main (gint argc, gchar *argv[])
{
	GtkWidget *main_widget;
	GtkWidget *cairo_widget;
	
	B_Window *b_window;
	b_window = (B_Window *) malloc(sizeof(B_Window));
	
	b_window->Launcher = g_ptr_array_new();
	
	printf ("asad %s\n",BOUDA_DATA);
	bouda_validate_config ();
	
	bouda_read_bouda_properties (g_strconcat (g_getenv("HOME"),C_PATH,NULL),b_window);
	bouda_read_icon_list (g_strconcat (g_getenv("HOME"),L_PATH,NULL), b_window);
	
	bouda_set_bouda_properties (b_window);
	g_ptr_array_foreach	(b_window->Launcher,(GFunc)bouda_set_icon_properties,NULL);	
	
	main_widget = bouda_main_widget (b_window);
	cairo_widget = bouda_cairo_widget (b_window);
						
	gtk_container_add (GTK_CONTAINER(main_widget),cairo_widget);
	
	return main_widget;
}



static void 
destroy (GtkWidget *widget,B_Window *b_window)
{
	g_ptr_array_free (b_window->Launcher,TRUE);
	g_strfreev (b_window->Order);
	g_free (b_window);
	gtk_main_quit();
}



void 
bouda_set_icon_properties (B_Launcher *b_launcher)
{
	b_launcher->Alpha=FALSE;
	b_launcher->Press=FALSE;
}



void 
bouda_set_bouda_properties (B_Window *b_window)
{
	b_window->Width  = b_window->Size * b_window->Launcher->len + 2 * b_window->Border ;
	b_window->Height = b_window->Size + 2 * b_window->Border;
}



void
gtk_widget_realize (GtkWidget *widget)
{
	xutils_set_window_type (GTK_WIDGET(widget)->window, PANEL_XUTILS_TYPE_DOCK);
}



static GtkWidget 
*bouda_cairo_widget (B_Window *b_window) 
{
	GtkWidget *widget;
	
	widget = gtk_cairo_new ();
	
	gtk_widget_add_events (widget,
						GDK_POINTER_MOTION_MASK |
						GDK_BUTTON_PRESS_MASK   |
						GDK_BUTTON_RELEASE_MASK);	
						
	g_signal_connect (G_OBJECT (widget), "button_press_event",
						G_CALLBACK (event_press), b_window);
						
	g_signal_connect (G_OBJECT (widget), "button_release_event",
						G_CALLBACK (event_release), b_window);
						
	g_signal_connect (G_OBJECT (widget), "motion_notify_event", 
						G_CALLBACK (event_motion), b_window);
	
	g_signal_connect (G_OBJECT(widget), "paint", 
						G_CALLBACK (bouda_cairo_repaint), b_window);
						
	gtk_widget_set_size_request (widget, b_window->Width, b_window->Height);
	
	return widget;
}



static GtkWidget 
*bouda_main_widget (B_Window *b_window) 
{
	GtkWidget *widget;
	
	widget = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	
	gtk_window_set_keep_below ((gpointer)widget, TRUE);
	
	gtk_window_move ((gpointer)widget,
						(gdk_screen_width() - b_window->Width)/2,
						gdk_screen_height() - b_window->Height);
						
	g_signal_connect(G_OBJECT(widget), "destroy",
						G_CALLBACK(destroy), b_window);
						 
	g_signal_connect (G_OBJECT (widget), "realize", 
						G_CALLBACK (gtk_widget_realize), NULL);	
	
	return widget;
}
