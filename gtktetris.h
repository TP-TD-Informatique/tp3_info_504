#ifndef TETRIS_GTKTETRIS_H
#define TETRIS_GTKTETRIS_H

#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>

#include "tetris.h"

#define TAILLE_CARRE 16

GtkWidget *createIHM();

GtkWidget *createArrowBtn(GtkArrowType type);

GtkWidget *createLabelBtn(char *label);

#endif //TETRIS_GTKTETRIS_H
