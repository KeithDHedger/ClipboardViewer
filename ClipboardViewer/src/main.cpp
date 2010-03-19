//
//Keith Hedger
//Tue Jun 12 16:22:48 BST 2007
//
//clipboardview.cpp
//

#include <gnome.h>
#include <glade/glade.h>
#include <glib/gstdio.h>
#include <glib.h>

#include "globals.h"

//GladeXML	*mainui;


gboolean check(gpointer data)
{
	GtkTextBuffer	*buffer;
	GtkTextIter	startIter;
	GtkTextIter	endIter;

	if (gtk_clipboard_wait_is_text_available(mainclipboard)==true)
		{
		buffer=gtk_text_view_get_buffer (GTK_TEXT_VIEW (glade_xml_get_widget(mainui,"textclip")));
		gchar	*clipText=gtk_clipboard_wait_for_text(mainclipboard);
		if (clipText==NULL)
			return true;
		gtk_text_buffer_get_bounds(buffer,&startIter,&endIter);

		gchar*	oldText=gtk_text_buffer_get_text(buffer,&startIter,&endIter,true);
		
		if (g_ascii_strcasecmp(clipText,oldText)!=0)
			gtk_text_buffer_set_text(buffer,clipText,-1);
		gtk_notebook_set_current_page(GTK_NOTEBOOK(glade_xml_get_widget(mainui,"cliptype")),0);
		g_free(clipText);
		g_free(oldText);
		}

	if (gtk_clipboard_wait_is_image_available(mainclipboard)==true)
		{
		GtkImage	*image=GTK_IMAGE(glade_xml_get_widget(mainui,"imageclip"));
		GdkPixbuf	*pixbuf=gtk_clipboard_wait_for_image(mainclipboard);
		if (pixbuf==NULL)
			return true;

		gtk_image_set_from_pixbuf (image,pixbuf);
		gtk_notebook_set_current_page(GTK_NOTEBOOK(glade_xml_get_widget(mainui,"cliptype")),1);
		g_object_unref(pixbuf);
		}

	return true;
}

void endProgram(GtkButton *button, gpointer window_ptr)
{
	gtk_main_quit();
}

int main(int argc, char **argv)
{

	GnomeProgram	*program;
	GtkWindow	*window;
	gchar		*gladepath;

	gtk_init(&argc,&argv);
	mainclipboard=gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);

	tempname=tempnam("./","image");
	strcat(tempname,".png");

	//printf("%s\n",tempname);
	//free(tempname);
	//return 0;
	if (argc>1 && g_ascii_strcasecmp(argv[1],"--nogui")==0)
		{
		GdkPixbuf	*image=gtk_clipboard_wait_for_image(mainclipboard);
		
		if (image!=NULL)
			{
			gdk_pixbuf_save(image,tempname, "png",NULL,NULL, NULL, NULL);
			g_object_unref((gpointer) image);
			g_printf(tempname);
			free(tempname);
			}
		else
			{
			gchar	*clipText=gtk_clipboard_wait_for_text(mainclipboard);
			
			if (clipText!=NULL)
				{
				g_printf(clipText);
				g_free(clipText);
				}
			}
		return 0;
		}

	if (argc>1 && g_ascii_strcasecmp(argv[1],"--query")==0)
		{
			GdkPixbuf	*image=gtk_clipboard_wait_for_image(mainclipboard);
			if (image!=NULL)
				{
				printf("image\n");
				g_object_unref((gpointer) image);
				return 0;
				}
			gchar	*clipText=gtk_clipboard_wait_for_text(mainclipboard);
			if (clipText!=NULL)
				{
				printf("text\n");
				g_free(clipText);
				return 0;
				}
		}

	if (argc>1)
		{
		printf("clipboardviewer %s: invalid option\n",argv[1]);
		printf("Usage:	clipboardviewer [--nogui]\n");
		return 1;
		}
		

	program = gnome_program_init("ClipboardViewer", "0.1",
                               LIBGNOMEUI_MODULE,
                               argc, argv,
                               GNOME_PROGRAM_STANDARD_PROPERTIES,
                               GNOME_PARAM_HUMAN_READABLE_NAME, "ClipboardViewer",
                               NULL);

	gladepath=gnome_program_locate_file(program,GNOME_FILE_DOMAIN_APP_DATADIR,
						"clipboardviewer.glade",
						true,
						NULL);

	if (g_file_test(GLADEFILE,G_FILE_TEST_EXISTS)==TRUE)
		{
		gladepath=GLADEFILE;
		prefixPathToPix=PATHTOPIX;
		prefixPathToScripts=PATHTOSCRIPTS;
		}
	else
		{
		gladepath=gnome_program_locate_file(program,GNOME_FILE_DOMAIN_APP_DATADIR,GLADENAME,true,NULL);
		prefixPathToPix=gnome_program_locate_file(program,GNOME_FILE_DOMAIN_APP_DATADIR,"pixmaps",true,NULL);
		prefixPathToScripts=gnome_program_locate_file(program,GNOME_FILE_DOMAIN_APP_DATADIR,"scripts",true,NULL);
		}

	mainui = glade_xml_new(gladepath, NULL, NULL);
	window = GTK_WINDOW(glade_xml_get_widget(mainui, "clipwindow"));
	gtk_window_stick(GTK_WINDOW(window));
	check(NULL);
	glade_xml_signal_connect_data(mainui,"endprogram",G_CALLBACK(endProgram),GUINT_TO_POINTER(window));

	g_timeout_add(1000,check,NULL);
	gtk_main();
	return 0;

}
