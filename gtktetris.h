#ifndef TETRIS_GTKTETRIS_H
#define TETRIS_GTKTETRIS_H

#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>

#include "tetris.h"

GtkWidget *canevas;

#define TAILLE_CARRE 16

#define BORDER 50
#define CANVAS_WIDTH TAILLE_CARRE * LARGEUR + 2 * BORDER // BORDER à gauche et BORDER à droite
#define CANVAS_HEIGHT TAILLE_CARRE * HAUTEUR + 3 * BORDER // BORDER en bas et 2*BORDER en haut

typedef struct {
    Grille grille;
    Piece pieces[NB_PIECES];
    int piece; // La piece actuelle
    int col; // La colonne actuelle
    int score; // Le score
    int delay; // Le délais
} Jeu;

void nouvellePiece(Jeu *jeu);

void createIHM(Jeu *jeu);

void dessineGrille(cairo_t *cr, Grille grille);

void dessinePiece(cairo_t *cr, Jeu *jeu);

void dessineCarre(cairo_t *cr, int ligne, int colonne, char c);

gboolean realize_evt_reaction(GtkWidget *widget, gpointer data);

gboolean expose_evt_reaction(GtkWidget *widget, GdkEventExpose *event, gpointer data);

GtkWidget *createArrowBtn(GtkArrowType type);

GtkWidget *createLabelBtn(char *label);

gboolean left(GtkWidget *widget, gpointer data);

gboolean down(GtkWidget *widget, gpointer data);

gboolean right(GtkWidget *widget, gpointer data);

gboolean new(GtkWidget *widget, gpointer data);

#endif //TETRIS_GTKTETRIS_H
