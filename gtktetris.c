#include "gtktetris.h"


int main(int argc, char *argv[]) {
    Jeu jeu;
    initialiseGrille(jeu.grille);
    initialisePieces(jeu.pieces);

    gtk_init(&argc, &argv);

    createIHM(&jeu);

    gtk_main();

    return EXIT_SUCCESS;
}

void createIHM(Jeu *jeu) {
    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    GtkWidget *mainBox = gtk_hbox_new(FALSE, 10);

    GtkWidget *leftBox = gtk_vbox_new(FALSE, 10);
    // Zone de dessin
    GtkWidget *canevas = gtk_drawing_area_new();
    gtk_drawing_area_size(GTK_DRAWING_AREA(canevas), TAILLE_CARRE * (LARGEUR + 4), TAILLE_CARRE * (HAUTEUR + 7));
    g_signal_connect(G_OBJECT(canevas), "realize", G_CALLBACK(realize_evt_reaction), jeu);
    g_signal_connect(G_OBJECT(canevas), "expose_event", G_CALLBACK(expose_evt_reaction), jeu);
    gtk_container_add(GTK_CONTAINER(leftBox), canevas);
    // Flèches
    GtkWidget *arrowBox = gtk_hbox_new(TRUE, 10);
    GtkWidget *leftArrow = createArrowBtn(GTK_ARROW_LEFT);
    g_signal_connect(leftArrow, "clicked", G_CALLBACK(left), NULL);
    GtkWidget *downArrow = createArrowBtn(GTK_ARROW_DOWN);
    g_signal_connect(downArrow, "clicked", G_CALLBACK(down), NULL);
    GtkWidget *rightArrow = createArrowBtn(GTK_ARROW_RIGHT);
    g_signal_connect(rightArrow, "clicked", G_CALLBACK(right), NULL);
    gtk_container_add(GTK_CONTAINER(arrowBox), leftArrow);
    gtk_container_add(GTK_CONTAINER(arrowBox), downArrow);
    gtk_container_add(GTK_CONTAINER(arrowBox), rightArrow);
    gtk_container_add(GTK_CONTAINER(leftBox), arrowBox);
    // Ajout du leftBox
    gtk_container_add(GTK_CONTAINER(mainBox), leftBox);

    GtkWidget *rightBox = gtk_vbox_new(TRUE, 10);
    // Boutons new et quit
    GtkWidget *btnBox = gtk_hbox_new(TRUE, 10);
    GtkWidget *newBtn = createLabelBtn("New");
    g_signal_connect(newBtn, "clicked", G_CALLBACK(new), NULL);
    GtkWidget *quitBtn = createLabelBtn("Quit");
    g_signal_connect(quitBtn, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_add(GTK_CONTAINER(btnBox), newBtn);
    gtk_container_add(GTK_CONTAINER(btnBox), quitBtn);
    gtk_container_add(GTK_CONTAINER(rightBox), btnBox);
    // Label score
    GtkWidget *scoreBox = gtk_hbox_new(TRUE, 10);
    GtkWidget *scoreLabel = gtk_label_new("Score");
    GtkWidget *scoreNLabel = gtk_label_new("0");
    gtk_container_add(GTK_CONTAINER(scoreBox), scoreLabel);
    gtk_container_add(GTK_CONTAINER(scoreBox), scoreNLabel);
    gtk_container_add(GTK_CONTAINER(rightBox), scoreBox);
    // Label delay
    GtkWidget *delayBox = gtk_hbox_new(TRUE, 10);
    GtkWidget *delayLabel = gtk_label_new("Delay");
    GtkWidget *delayNLabel = gtk_label_new("");
    gtk_container_add(GTK_CONTAINER(delayBox), delayLabel);
    gtk_container_add(GTK_CONTAINER(delayBox), delayNLabel);
    gtk_container_add(GTK_CONTAINER(rightBox), delayBox);
    // Ajout du rightBox
    gtk_container_add(GTK_CONTAINER(mainBox), rightBox);

    gtk_container_add(GTK_CONTAINER(window), mainBox);
    gtk_widget_show_all(window);
}

gboolean realize_evt_reaction(GtkWidget *widget, gpointer data) {
    gtk_widget_queue_draw(widget);
    return TRUE;
}

gboolean expose_evt_reaction(GtkWidget *widget, GdkEventExpose *event, gpointer data) {
    // c'est la structure qui permet d'afficher dans une zone de dessin via Cairo
    cairo_t *cr = gdk_cairo_create(widget->window);
    cairo_set_source_rgb(cr, 1, 1, 1); // choisit le blanc.
    cairo_paint(cr); // remplit tout dans la couleur choisie.

    cairo_set_source_rgb(cr, 0, 1, 0);
    cairo_rectangle(cr, 50, 50, 100, 100); // x, y, largeur, hauteur
    cairo_fill_preserve(cr); // remplit la forme actuelle (un rectangle)
    // => "_preserve" garde la forme (le rectangle) pour la suite

    cairo_set_line_width(cr, 3);
    cairo_set_source_rgb(cr, 0, 0.5, 0);
    cairo_stroke(cr); // trace la forme actuelle (le même rectangle)
    // => pas de "_preserve" donc la forme (le rectangle) est oublié.

    // On a fini, on peut détruire la structure.
    cairo_destroy(cr);
    return TRUE;
}

GtkWidget *createArrowBtn(GtkArrowType type) {
    GtkWidget *button = gtk_button_new();
    GtkWidget *arrow = gtk_arrow_new(type, GTK_SHADOW_OUT);
    gtk_container_add(GTK_CONTAINER(button), arrow);
    gtk_widget_show_all(button);

    return button;
}

GtkWidget *createLabelBtn(char *label) {
    GtkWidget *btn = gtk_button_new_with_label(label);
    gtk_widget_show(btn);
    return btn;
}

gboolean left(GtkWidget *widget, gpointer data) {
    return TRUE;
}

gboolean down(GtkWidget *widget, gpointer data) {
    return TRUE;
}

gboolean right(GtkWidget *widget, gpointer data) {
    return TRUE;
}

gboolean new(GtkWidget *widget, gpointer data) {
    return TRUE;
}