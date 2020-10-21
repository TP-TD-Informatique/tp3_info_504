#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>

#include "tetris.h"


int main(int argc, char *argv[]) {
    GtkWidget *window;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_show(window);

    GtkWidget *quitBtn;
    quitBtn = gtk_button_new_with_label("Quit");
    g_signal_connect(quitBtn, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_add(GTK_CONTAINER(window), quitBtn);
    gtk_widget_show(quitBtn);

    gtk_main();

    return EXIT_SUCCESS;
}