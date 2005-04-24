#include <gtk/gtk.h>
#include <glib.h>

#if HAVE_CONFIG_H
 #include <config.h>
#endif

#define LAUNCHER "LAUNCHER"
#define L_PATH "/.bouda/launchers/"
#define C_PATH "/.bouda/bouda.config"
#define M_PATH "/.bouda/"

#define L1 "firefox.desktop"
#define L2 "nautilus.desktop"
#define L3 "terminal.desktop"

GtkWidget *bouda_main();

typedef struct
{
	gchar *Exec;
	gchar *Icon;
	gchar *Name;
	gchar *Generic;
	gchar *Comment;
	gchar *Buffer;
	
	guint Width;
	guint Height;
	guint Possition;

	gboolean Terminal;
	gboolean Alpha;
	gboolean Press;
	
} B_Launcher;


typedef struct
{
	guint Width;
	guint Height;
	guint Border;
	guint Size;
	guint Length;
	gchar **Order;
	GPtrArray *Launcher;
	
} B_Window;
