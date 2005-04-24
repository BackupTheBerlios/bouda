#include <gtk/gtk.h>

#include "bouda.h"
#include "cairo-canvas.h"

static void bouda_cairo_draw_border (cairo_t *cr, guint width, guint height) ;
static void bouda_cairo_draw_icons (cairo_t *cr, B_Window *b_window);
static void bouda_cairo_draw_background (cairo_t *cr, guint width, guint height);

void 
bouda_cairo_repaint (GtkWidget *widget, cairo_t *cr, B_Window *b_window)
{	

	bouda_cairo_draw_background (cr, b_window->Width, b_window->Height);
	bouda_cairo_draw_icons (cr , b_window);
	bouda_cairo_draw_border (cr, b_window->Width, b_window->Height);
	
}

static void 
bouda_cairo_draw_border (cairo_t *cr, guint width, guint height) 
{

	cairo_set_line_width (cr,0.5);
	cairo_move_to (cr, 0.5,0.5); 
	cairo_line_to (cr, 0.5,height);
	cairo_move_to (cr, 0.5,0.5);
	cairo_line_to (cr, width,0.5);
	cairo_move_to (cr, width-0.5,0.5);
	cairo_line_to (cr, width-0.5,height);
	cairo_stroke (cr);
	
}

static void 
bouda_cairo_draw_icons (cairo_t *cr, B_Window *b_window)
{
	guint i;
	B_Launcher *b_launcher;
	cairo_surface_t *image;
	gdouble scale_x, scale_y; 
	
	for (i=0; i < b_window->Launcher->len; i++) {
	
		cairo_save (cr);
		b_launcher = g_ptr_array_index(b_window->Launcher,i);
		
		image = cairo_surface_create_for_image (b_launcher->Buffer, 
												CAIRO_FORMAT_ARGB32,
												b_launcher->Width,
												b_launcher->Height,
												b_launcher->Width * 4);
												
		cairo_surface_set_filter (image, CAIRO_FILTER_BEST);
		
		scale_x = (gdouble)b_window->Size / (gdouble)b_launcher->Width;
		scale_y = (gdouble)b_window->Size / (gdouble)b_launcher->Height;
		
		cairo_scale (cr, scale_x, scale_y);
		
		cairo_translate(cr, b_window->Border/scale_x + 
								b_launcher->Width*b_launcher->Possition,							
							b_window->Border/scale_x);
							
		cairo_move_to (cr, 0,0);
		
		cairo_show_surface (cr, image,b_launcher->Width,b_launcher->Width);
		cairo_surface_destroy (image);		
		
		cairo_restore (cr);
	}
}

static void 
bouda_cairo_draw_background (cairo_t *cr, guint width, guint height) 
{
	cairo_save (cr);
	cairo_rectangle (cr, 0, 0, width, height);
	cairo_set_rgb_color (cr, 0.68, 0.76, 0.83);
	cairo_fill (cr);
	cairo_restore (cr);
}
