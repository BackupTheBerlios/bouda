#include <glib.h>
#include <string.h>
#include <stdlib.h>

#include "bouda.h"

int 
bouda_read_bouda_properties (const char *File, B_Window *b_window )
{

	GKeyFile *GKeyConfigFile;
	GKeyConfigFile = g_key_file_new ();
	g_key_file_load_from_file (GKeyConfigFile, File, 0, NULL);
	
		
	b_window->Size=g_key_file_get_integer  (GKeyConfigFile, "CONFIG", "Size", NULL);
	b_window->Border=g_key_file_get_integer  (GKeyConfigFile, "CONFIG", "Border", NULL);
	b_window->Order = g_key_file_get_string_list (GKeyConfigFile, "CONFIG","Order",&b_window->Length,NULL);	
	
	g_key_file_free (GKeyConfigFile);
	
	return 0;
}
