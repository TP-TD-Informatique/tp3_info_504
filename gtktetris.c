#include "gtktetris.h"


int main(int argc, char *argv[]) {
    srand(time(0));

    Jeu jeu;
    initialiseGrille(jeu.grille);
    initialisePieces(jeu.pieces);
    jeu.score = 0;
    nouvellePiece(&jeu);

    gtk_init(&argc, &argv);

    createIHM(&jeu);

    gtk_main();

    return EXIT_SUCCESS;
}

void nouvellePiece(Jeu *jeu) {
    jeu->piece = (int) (((double) rand() / ((double) RAND_MAX)) * (NB_PIECES));
    jeu->col = LARGEUR / 2 - (jeu->pieces[jeu->piece].largeur / 2);
}

void createIHM(Jeu *jeu) {
    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    GtkWidget *mainBox = gtk_hbox_new(FALSE, 10);

    GtkWidget *leftBox = gtk_vbox_new(FALSE, 10);
    // Zone de dessin
    canevas = gtk_drawing_area_new();
    gtk_drawing_area_size(GTK_DRAWING_AREA(canevas), CANVAS_WIDTH, CANVAS_HEIGHT);
    g_signal_connect(G_OBJECT(canevas), "realize", G_CALLBACK(realize_evt_reaction), jeu);
    g_signal_connect(G_OBJECT(canevas), "expose_event", G_CALLBACK(expose_evt_reaction), jeu);
    gtk_container_add(GTK_CONTAINER(leftBox), canevas);
    // Flèches
    GtkWidget *arrowBox = gtk_hbox_new(TRUE, 10);
    GtkWidget *leftArrow = createArrowBtn(GTK_ARROW_LEFT);
    g_signal_connect(leftArrow, "clicked", G_CALLBACK(left), jeu);
    GtkWidget *downArrow = createArrowBtn(GTK_ARROW_DOWN);
    g_signal_connect(downArrow, "clicked", G_CALLBACK(down), jeu);
    GtkWidget *rightArrow = createArrowBtn(GTK_ARROW_RIGHT);
    g_signal_connect(rightArrow, "clicked", G_CALLBACK(right), jeu);
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
    g_signal_connect(newBtn, "clicked", G_CALLBACK(new), jeu);
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

void dessineGrille(cairo_t *cr, Grille grille) {
    // Fond de la grille
    cairo_pattern_t *pat = cairo_pattern_create_linear(0, 0, 0, CANVAS_HEIGHT);
    cairo_pattern_add_color_stop_rgba(pat, 1, 0, 0, 0, 1);
    cairo_pattern_add_color_stop_rgba(pat, 0, 1, 1, 1, 1);
    cairo_rectangle(cr, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);
    cairo_set_source(cr, pat);
    cairo_fill(cr);
    cairo_pattern_destroy(pat);

    // Zone blanche pour la grille effective
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_rectangle(cr, BORDER, 0, TAILLE_CARRE * LARGEUR, TAILLE_CARRE * HAUTEUR + 2 * BORDER);
    cairo_fill(cr);

    for (int i = 0; i < HAUTEUR; ++i) {
        for (int j = 0; j < LARGEUR; ++j) {
            char c = lireCase(grille, i, j);
            if (c != ' ') {
                dessineCarre(cr, HAUTEUR - i - 1, j, c);
            }
        }
    }
}

void dessinePiece(cairo_t *cr, Jeu *jeu) {
    Piece piece = jeu->pieces[jeu->piece];
    for (int i = piece.hauteur - 1; i >= 0; --i) {
        for (int j = 0; j < piece.largeur; ++j) {
            char c = piece.forme[i][j];
            if (c != ' ') {
                dessineCarre(cr, -i, jeu->col + j, c);
            }
        }
    }
}

void dessineCarre(cairo_t *cr, int ligne, int colonne, char c) {
    switch (c) {
        case '%':
            cairo_set_source_rgb(cr, 1, 0, 0);
            break;

        case '@':
            cairo_set_source_rgb(cr, 0, 1, 0);
            break;

        case 'l':
            cairo_set_source_rgb(cr, 0, 0, 1);
            break;

        default:
            cairo_set_source_rgb(cr, 0, 0, 0);
    }
    cairo_rectangle(cr, colonne * TAILLE_CARRE + BORDER, ligne * TAILLE_CARRE + 2 * BORDER, TAILLE_CARRE, TAILLE_CARRE);
    cairo_fill_preserve(cr);

    cairo_set_line_width(cr, 2);
    switch (c) {
        case '%':
            cairo_set_source_rgb(cr, 0.5, 0, 0);
            break;

        case '@':
            cairo_set_source_rgb(cr, 0, 0.5, 0);
            break;

        case 'l':
            cairo_set_source_rgb(cr, 0, 0, 0.5);
            break;

        default:
            cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
    }
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_BEVEL);
    cairo_stroke(cr);
}

gboolean realize_evt_reaction(GtkWidget *widget, gpointer data) {
    gtk_widget_queue_draw(widget);
    return TRUE;
}

gboolean expose_evt_reaction(GtkWidget *widget, GdkEventExpose *event, gpointer data) {
    printf("dessine\n");
    Jeu *jeu = (Jeu *) data;
    cairo_t *cr = gdk_cairo_create(widget->window);
    dessineGrille(cr, jeu->grille);
    dessinePiece(cr, jeu);
    cairo_destroy(cr);
    return TRUE;
}

GtkWidget *createArrowBtn(GtkArrowType type) {
    GtkWidget *button = gtk_button_new();
    GtkWidget *arrow = gtk_arrow_new(type, GTK_SHADOW_NONE);
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
    Jeu *jeu = (Jeu *) data;
    jeu->col--;
    if (jeu->col < 0) jeu->col = 0;
    gtk_widget_queue_draw(canevas);
    return TRUE;
}

gboolean down(GtkWidget *widget, gpointer data) {
    Jeu *jeu = (Jeu *) data;
    Piece piece = jeu->pieces[jeu->piece];
    int hauteur2 = hauteurExacte(jeu->grille, jeu->col, piece);
    ecrirePiece(jeu->grille, piece, jeu->col, hauteur2);
    jeu->score += nettoyer(jeu->grille);
    nouvellePiece(jeu);
    gtk_widget_queue_draw(canevas);
    return TRUE;
}

gboolean right(GtkWidget *widget, gpointer data) {
    Jeu *jeu = (Jeu *) data;
    jeu->col++;
    if (jeu->col + jeu->pieces[jeu->piece].largeur >= LARGEUR) jeu->col = LARGEUR - jeu->pieces[jeu->piece].largeur;
    gtk_widget_queue_draw(canevas);
    return TRUE;
}

gboolean new(GtkWidget *widget, gpointer data) {
    return TRUE;
}