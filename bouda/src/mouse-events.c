#include <gtk/gtk.h>
#include <glib/gprintf.h>

#include "bouda.h"
       

static void bouda_exec_program (gchar *executable);

gboolean
event_release (GtkWidget      *widget,
               GdkEventButton *bev,
               B_Window       *b_window)
{
	guint i;
	guint size, border;
	
	B_Launcher *b_launcher;
	
	size = b_window->Size;
	border = b_window->Border;
	
	for (i=0; i < b_window->Launcher->len; i++) {
		if ((bev->x > border+size*i) && 
			(bev->x < border+size*(i+1)) && 
			(bev->y > border) &&
			(bev->y < border+size)) 
		{
			b_launcher = g_ptr_array_index ( b_window->Launcher, i );
			bouda_exec_program ( b_launcher->Exec );
			g_printf ( "%s\n", b_launcher->Exec );
		}
	}
	
	return TRUE;
}


gboolean
event_motion (GtkWidget      *widget,
              GdkEventMotion *mev,
              B_Window       *b_window)
{
	return TRUE;
}


gboolean
event_press (GtkWidget      *widget,
             GdkEventButton *bev,
             B_Window       *b_window)
{
	return TRUE;
}


static void
bouda_exec_program (gchar *executable)
{
	gchar **argv;

	argv = g_new0 (char *, 4);
	argv [0] = g_strdup ("/bin/sh");
	argv [1] = g_strdup ("-c");
	argv [2] = g_strdup (executable);


	g_spawn_async ( NULL,
					argv,
					NULL,
					G_SPAWN_SEARCH_PATH | 
					G_SPAWN_STDERR_TO_DEV_NULL | 
					G_SPAWN_STDOUT_TO_DEV_NULL,
					NULL,
					NULL,
					NULL,
					NULL ); 

}
