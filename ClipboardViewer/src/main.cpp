
//Mon 31 Jul 2006 12:30:55 BST 

#include <gnome.h>
#include <glade/glade.h>
#include <glib/gstdio.h>
#include <glib.h>

#include "globals.h"

gint delete_event(GtkWidget *widget, GdkEvent event, gpointer data)
{
	g_printf("\n%s\n","BYE!");
	gtk_main_quit();
	return TRUE;
}

void runAScript(gchar *commandLine)
{
	g_warning("%s",commandLine);
	g_spawn_command_line_sync(commandLine,NULL,NULL,NULL,NULL);
}

void doOk(GtkButton *button, gpointer window_ptr)
{
	g_printf("ok clicked\n");
}

void doCancel(GtkButton *button, gpointer window_ptr)
{
	g_printf("cancel clicked\n");
}

mainSignals theSignals[]={
				{"okclicked",doOk},
				{"cancelclicked",doCancel},
				{NULL,NULL}
			};

int main(int argc, char **argv)
{
	
	GnomeProgram	*program;
	unsigned int	cnt=0;

	program = gnome_program_init("ClipboardViewer", "0.1",
                               LIBGNOMEUI_MODULE,
                               argc, argv,
                               GNOME_PROGRAM_STANDARD_PROPERTIES,
                               GNOME_PARAM_HUMAN_READABLE_NAME, "ClipboardViewer",
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
	mainwindow = GTK_WINDOW(glade_xml_get_widget(mainui, "mainwindow"));
	g_signal_connect(mainwindow, "delete-event", G_CALLBACK(delete_event), NULL);

	while (theSignals[cnt].name!=NULL)
		{
		glade_xml_signal_connect_data(mainui,theSignals[cnt].name,G_CALLBACK(theSignals[cnt].fptr),GUINT_TO_POINTER(mainwindow));
		cnt++;
		}
	
	gtk_main();
	return 0;
}

