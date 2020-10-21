#ifndef TETRIS_GTKTETRIS_H
#define TETRIS_GTKTETRIS_H

#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>

#include "tetris.h"

#define TAILLE_CARRE 16

int val0 = 17;

GtkWidget *createIHM();

GtkWidget *createArrowBtn(GtkArrowType type);

GtkWidget *createLabelBtn(char *label);

gboolean left(GtkWidget *widget, gpointer data);

gboolean down(GtkWidget *widget, gpointer data);

gboolean right(GtkWidget *widget, gpointer data);

gboolean new(GtkWidget *widget, gpointer data);

#endif //TETRIS_GTKTETRIS_H
