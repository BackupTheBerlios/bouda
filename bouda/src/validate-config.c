#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gstdio.h>
#include "bouda.h"

static void check_main_direcory (const gchar *home_mpath);
static void check_launcher_directory (const gchar *home_lpath);
static void check_config_file (const gchar *main_cpath, const gchar *home_cpath);
static void copy_text_file (const gchar *input, const gchar *output); 
void 
bouda_validate_config ()
{
	// check if main directory
	// is being created and if not
	// create default directory with
	// values from /usr/share/bouda/
	// and put some launchers in it
	
	check_main_direcory ( g_strconcat (g_getenv("HOME"), M_PATH, NULL) );
	
	// create launcher directory
	
	check_launcher_directory ( g_strconcat (g_getenv("HOME"), L_PATH, NULL) );
	
	// copy main config file from
	// /usr/share/bouda
	
	check_config_file (BOUDA_CONFIG, g_strconcat (g_getenv("HOME"), C_PATH, NULL) );
}


static void
check_main_direcory (const gchar *home_mpath)
{
	if ( ! g_file_test (home_mpath, G_FILE_TEST_EXISTS | G_FILE_TEST_IS_DIR) ) 
	{
		if ( g_mkdir (home_mpath,0711) == -1 ) 
		{
			g_warning ("Could not create %s.\n", home_mpath);
		}
	}
}


static void
check_launcher_directory (const gchar *home_lpath)
{
	if ( ! g_file_test (home_lpath, G_FILE_TEST_EXISTS | G_FILE_TEST_IS_DIR) ) 
	{
		if ( g_mkdir (home_lpath,0711) == -1 ) 
		{
			g_warning ("Could not create %s.\n", home_lpath);
		}	
	}
	
	// copy first launcher
		
	if ( ! g_file_test ( g_strconcat (home_lpath, L1, NULL) , 
						G_FILE_TEST_EXISTS | 
						G_FILE_TEST_IS_REGULAR ) ) 
	{
		copy_text_file (g_strconcat (BOUDA_LAUNCHERS,"/", L1, NULL), 
						g_strconcat (home_lpath, L1, NULL) );
	}
	
	// copy second launcher
	
	if ( ! g_file_test ( g_strconcat (home_lpath, L2, NULL), 
						G_FILE_TEST_EXISTS | 
						G_FILE_TEST_IS_REGULAR ) ) 
	{
		copy_text_file (g_strconcat (BOUDA_LAUNCHERS,"/", L2, NULL), 
						g_strconcat (home_lpath, L2, NULL) );		
	}
	
	// copy third launcher
	
	if ( ! g_file_test ( g_strconcat (home_lpath, L3, NULL), 
						G_FILE_TEST_EXISTS | 
						G_FILE_TEST_IS_REGULAR ) ) 
	{
		copy_text_file (g_strconcat (BOUDA_LAUNCHERS,"/", L3, NULL), 
						g_strconcat (home_lpath, L3, NULL) );		
	}	
}


static void
check_config_file (const gchar *main_cpath, const gchar *home_cpath)
{	
	printf ("%s %s\n", main_cpath, home_cpath);
	if ( ! g_file_test ( home_cpath, G_FILE_TEST_EXISTS | G_FILE_TEST_IS_REGULAR ) ) 
	{
		copy_text_file (main_cpath, home_cpath); // correct paths
	}
}


/* 
Use this function only to copy TEXT files.
It will not work with binary files.
*/

static void
copy_text_file (const gchar *input, const gchar *output) 
{
	guint ch; 
   	FILE *finput, *foutput;
		
	finput = fopen(input, "r");
	foutput = fopen(output, "w");
		
	while( (ch = fgetc(finput)) != EOF)
	{
		fputc (ch, foutput);
	}
		
	fclose (finput);
	fclose (foutput);		
}




