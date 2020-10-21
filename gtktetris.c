#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>

#include "tetris.h"


int main(int argc, char *argv[]) {
    Grille g;
    Piece tabPieces[NB_PIECES];
    initialisePieces(tabPieces);
    initialiseGrille(g);
    afficheGrille(g);
    return 0;
}