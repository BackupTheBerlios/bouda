#include <glib.h>
#include <string.h>
#include <stdlib.h>

#include "bouda.h"
#include "read-png.h"

static gboolean bouda_get_icon_values (B_Launcher *b_launcher, GKeyFile *GKeyIconFile, gchar *File);

int bouda_read_icon_list (const char *Path,	B_Window *b_window)
{
	B_Launcher *b_launcher;
	GKeyFile *GKeyIconFile;	
	guint pos=0;
	guint i;
	gchar *File;
	gboolean correct;
	
	for (i=0; i < b_window->Length; i++) 
	{
		GKeyIconFile = g_key_file_new ();
		File=(gchar *) malloc(sizeof(gchar));
	
		File = g_strconcat (Path,b_window->Order[i],".desktop",NULL);
		
		// load g_key_file for file and if something goes wrong
		// show warning and skip tjis launcher
		
		if ( ! g_key_file_load_from_file (GKeyIconFile, File, 0, NULL)) 
		{
			g_warning ("Could not load launcher \"%s\"!\n",	b_window->Order[i]);
			continue ;
		}
	
		b_launcher = (B_Launcher *) malloc(sizeof(B_Launcher));
		
		// check if launcher is set OK
		
		correct = bouda_get_icon_values (b_launcher, GKeyIconFile, File);
		
		g_free (File);
		
		// add launcher to gpointer array if evrything is set OK
		
		if (correct == TRUE) 
		{
			b_launcher->Possition = pos; // set icon possition
			pos = pos+1; 
			g_ptr_array_add (b_window->Launcher, (gpointer) b_launcher); 
		} else {
			g_free (b_launcher);
		}
		
		g_key_file_free (GKeyIconFile); 

	}

	return 0;
}

static gboolean
bouda_get_icon_values (B_Launcher *b_launcher, 
					   GKeyFile *GKeyIconFile,
					   gchar *File)
{

	// check if default Groups is correct
	// group is same for all launchers
	
	if (! g_key_file_has_group (GKeyIconFile,LAUNCHER)) 
	{
		g_warning ("Wrong group in launcher. Replace it to %s.\n",LAUNCHER);
		return FALSE;
	}
	
	
	// check if Exec has been set and if not, show a warning 
	// but still show the launcher
	
	if (g_key_file_has_key (GKeyIconFile,LAUNCHER, "Exec", NULL)) 
	{
		b_launcher->Exec = g_key_file_get_string (GKeyIconFile, LAUNCHER, "Exec", NULL);
	} 
	else 
	{
		b_launcher->Exec = g_strconcat ("/usr/bin/none",NULL);
		g_warning ("No Exec is set for %s\n",File);
	}
	
	
	// check if Icon has been set and if not, show a warning
	// and return FALSE
	
	if ( g_key_file_has_key (GKeyIconFile, LAUNCHER, "Icon", NULL) ) 
	{ 	
		b_launcher->Icon = g_key_file_get_string (GKeyIconFile, LAUNCHER, "Icon", NULL);
		
		// check if icon starts with ~ , and change ~ to its home dirctory
		
		if (b_launcher->Icon == g_strrstr (b_launcher->Icon, "~" ) ) 
		{
			// asign new value to b_launcher->Icon 
			b_launcher->Icon = g_strconcat (g_getenv("HOME"), b_launcher->Icon + 1, NULL);
		}
		
		if ( b_launcher->Icon != g_strrstr (b_launcher->Icon, "~" ) && 
			 b_launcher->Icon != g_strrstr (b_launcher->Icon, "/" ) )
		{
			if (g_file_test (  g_strconcat (BOUDA_PIXMAPS,"/", b_launcher->Icon, NULL),
																G_FILE_TEST_EXISTS | 
															G_FILE_TEST_IS_REGULAR )) 
			{
				b_launcher->Icon = g_strconcat (BOUDA_PIXMAPS,
												"/",
												b_launcher->Icon, 
												NULL) ;
			} 
			else if (g_file_test (  g_strconcat ("/usr/share/pixmaps/", b_launcher->Icon , NULL), 
																			G_FILE_TEST_EXISTS | 
																		G_FILE_TEST_IS_REGULAR )) 
			{
				b_launcher->Icon = g_strconcat ("/usr/share/pixmaps/", 
												b_launcher->Icon, 
												NULL) ;
			}
		}
		
		if (! g_file_test ( b_launcher->Icon, G_FILE_TEST_EXISTS | G_FILE_TEST_IS_REGULAR )) 
		{
			b_launcher->Icon = g_strconcat (BOUDA_PIXMAPS,
											"/", 
											"none.png", 
											NULL) ;
		}											
		
	} 
	else 
	{
		g_warning ("No Icon is set for %s. Skipping this launcher.\n", b_launcher->Icon);
		return FALSE;
	}
	
	
	// get Name Comment and Terminal values
	// they are not nessesary and no warning is shown
	
	
	// check if launcher has a name set 
	
	if ( g_key_file_has_key (GKeyIconFile, LAUNCHER, "Name", NULL) ) 
	{	
		b_launcher->Name = g_key_file_get_string (GKeyIconFile, LAUNCHER, "Name", NULL);	
	}
	
	
	// check if launcher has comment set
	
	if ( g_key_file_has_key (GKeyIconFile, LAUNCHER, "Comment", NULL) ) 
	{		
		b_launcher->Comment = g_key_file_get_string (GKeyIconFile, LAUNCHER, "Comment", NULL);	
	}
	
	
	// check if launcher should start from terminal
	
	if ( g_key_file_has_key (GKeyIconFile,LAUNCHER, "Terminal", NULL) ) 
	{		
		b_launcher->Terminal = g_key_file_get_boolean (GKeyIconFile, LAUNCHER, "Terminal", NULL);		
	}
	
	
	// reads png from the file and returns 0 if successful
	// else if 1 is returned show a warning and 
	// return FALSE
	
	
	if ( read_png (b_launcher->Icon, &b_launcher->Buffer, 
					&b_launcher->Width,	&b_launcher->Height) ) 
	{
		g_warning ("Could not load %s\n",b_launcher->Icon);
		return FALSE;
	}	
	
	// if everything goes fine, return TRUE
	
	return TRUE;
}
