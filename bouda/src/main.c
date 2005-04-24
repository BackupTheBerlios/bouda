#include <glib.h>
#include <gtk/gtk.h>

#include "bouda.h"

gint 
main (gint argc, gchar **argv)
{
	gtk_init(&argc, &argv);
	
	GtkWidget *window;
	window = bouda_main (argc, argv);
	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
