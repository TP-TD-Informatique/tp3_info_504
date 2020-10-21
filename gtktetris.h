#ifndef TETRIS_GTKTETRIS_H
#define TETRIS_GTKTETRIS_H

#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>

#include "tetris.h"

#define TAILLE_CARRE 16

typedef struct {
    Grille grille;
    Piece pieces[NB_PIECES];
    int piece; // La piece actuelle
    int col; // La colonne actuelle
    int score; // Le score
    int delay; // Le délais
} Jeu;

void createIHM(Jeu *jeu);

gboolean realize_evt_reaction(GtkWidget *widget, gpointer data);

gboolean expose_evt_reaction(GtkWidget *widget, GdkEventExpose *event, gpointer data);

GtkWidget *createArrowBtn(GtkArrowType type);

GtkWidget *createLabelBtn(char *label);

gboolean left(GtkWidget *widget, gpointer data);

gboolean down(GtkWidget *widget, gpointer data);

gboolean right(GtkWidget *widget, gpointer data);

gboolean new(GtkWidget *widget, gpointer data);

#endif //TETRIS_GTKTETRIS_H
