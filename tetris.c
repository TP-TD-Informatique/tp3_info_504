#include "tetris.h"

void initialiseGrille(Grille grille) {
    for (int i = 0; i < HAUTEUR; ++i) { // Pour chaque ligne
        for (int j = 0; j < LARGEUR; ++j) { // Pour chaque case de la ligne
            grille[i][j] = ' ';
        }
    }
}

char lireCase(Grille grille, int ligne, int colonne) {
    if ((colonne < LARGEUR && colonne >= 0) &&
        (ligne < HAUTEUR && ligne >= 0)) // Si les coordonnées sont dans la grille
        return grille[ligne][colonne];
    return ' ';
}

void ecrireCase(Grille grille, int ligne, int colonne, char c) {
    if ((colonne < LARGEUR && colonne >= 0) &&
        (ligne < HAUTEUR && ligne >= 0)) // Si les coordonnées sont dans la grille
        grille[ligne][colonne] = c;
    else
        printf("Impossible d'écrire ici (%d:%d)\n", ligne, colonne);
}

void afficheGrille(Grille grille) {
    // Impression de la grille
    for (int i = HAUTEUR - 1; i >= 0; i--) { // Pour chaque ligne
        printf("||");
        for (int j = 0; j < LARGEUR; j++) { // Pour chaque case de la ligne
            printf("%c", lireCase(grille, i, j));
        }
        printf("||\n");
    }
    // Impression de la barre de séparation
    printf("||");
    for (int i = 0; i < LARGEUR; ++i) printf("|");
    printf("||\n");
    // Impression des numéros de colonnes
    int borne = 1;
    while (borne < LARGEUR) borne *= 10; // Récupération de la puissance 10 la plus proche
    borne /= 10;

    for (int i = borne; i >= 1; i /= 10) { // Pour chaque puissance 10
        printf("  ");
        int l = 0;
        for (int j = 0; j < LARGEUR; ++j) {
            if (j % i == 0) printf("%d", l++); // Ecrit chaque mutiple de la puissance
            else printf(" ");
            if (l > 9) l = 0;
        }
        printf("\n");
    }
}

int hauteurPlat(Grille grille, int debut, int fin) {
    int max = 0;

    if (debut <= fin && (debut >= 0 && debut < LARGEUR) &&
        (fin >= 0 && fin < LARGEUR)) { // Si les colonnes sont dans la grille
        for (int c = debut; c <= fin; ++c) {
            int i = 0;
            while (grille[i][c] != ' ' && i < HAUTEUR) i++; // Tant qu'il y a une pièce dans la case

            if (i > max) max = i;
        }
    } else
        printf("L'interval (%d:%d) n'est pas correct\n", debut, fin);

    return max;
}

int hauteurPiece(Piece piece, int colonne) {
    int hauteur = 0;
    if (colonne >= 0 && colonne < piece.largeur) { // Si la colonne est dans la pièce
        for (int i = 0; i < piece.hauteur; ++i) { // Pour chaque ligne de la colonne
            if (piece.forme[i][colonne] != ' ') hauteur++; // Si ce n'est pas un espace, incrémente la hauteur
        }
    }

    return hauteur;
}

int videSousPiece(Piece piece, int colonne) {
    int vide = 0;
    if (colonne >= 0 && colonne < piece.largeur) { // Si la colonne est dans la pièce
        while (piece.forme[vide][colonne] == ' ' && vide < piece.hauteur)
            vide++; // Tant qu'on n'a pas atteint le dessous de la pièce
    }

    return vide;
}

int hauteurExacte(Grille grille, int colonne, Piece piece) {
    int max = 0; // La hauteur max de la colonne
    int bas = 0; // Le vide sous la pièce
    for (int i = colonne; i < colonne + piece.largeur; ++i) {
        int hauteurC = hauteurPlat(grille, i, i);
        int hauteurP = hauteurPiece(piece, i - colonne);

        if (hauteurP + hauteurC > max) {
            max = hauteurC;
            bas = videSousPiece(piece, i - colonne);
        }
    }

    return max - bas;
}

void supprimerLigne(Grille grille, int ligne) {
    if (ligne < HAUTEUR && ligne >= 0) {
        for (int i = 0; i < LARGEUR; ++i) {
            grille[ligne][i] = ' '; // Efface la ligne
        }

        for (int i = ligne; i < HAUTEUR - 1; ++i) {
            for (int j = 0; j < LARGEUR; ++j) { // Décale les lignes supérieures
                grille[i][j] = grille[i + 1][j];
            }
        }
    } else
        printf("Impossible de supprimer la ligne %d\n", ligne);
}

bool lignePleine(Grille grille, int ligne) {
    if (ligne >= 0 && ligne < HAUTEUR) { // Si la ligne est dans la grille
        for (int i = 0; i < LARGEUR; ++i) { // Pour chaque case de la ligne
            if (grille[ligne][i] == ' ') return false; // Si la ligne contient un espace elle est pas pleine
        }
    } else
        return false;

    return true;
}

int nettoyer(Grille grille) {
    int result = 0;
    for (int i = HAUTEUR - 1; i >= 0; i--) { // Pour chaque ligne de la grille en partant d'en haut
        if (lignePleine(grille, i)) { // Si la ligne est pleine
            result++; // +1 au score
            supprimerLigne(grille, i); // Supprime cette ligne et décale vers le bas les lignes supérieures
        }
    }

    return result;
}

// _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-.

void initialisePieces(Piece pieces[NB_PIECES]) {
    // Ajout des formes de pièces
    pieces[0].hauteur = 2;
    pieces[0].largeur = 2;
    pieces[0].forme[1] = "%%";
    pieces[0].forme[0] = "%%";

    pieces[1].hauteur = 2;
    pieces[1].largeur = 3;
    pieces[1].forme[1] = " @ ";
    pieces[1].forme[0] = "@@@";
    pieces[2].hauteur = 2;
    pieces[2].largeur = 3;
    pieces[2].forme[1] = "@@@";
    pieces[2].forme[0] = " @ ";
    pieces[3].hauteur = 3;
    pieces[3].largeur = 2;
    pieces[3].forme[2] = "@ ";
    pieces[3].forme[1] = "@@";
    pieces[3].forme[0] = "@ ";
    pieces[4].hauteur = 3;
    pieces[4].largeur = 2;
    pieces[4].forme[2] = " @";
    pieces[4].forme[1] = "@@";
    pieces[4].forme[0] = " @";

    pieces[5].hauteur = 4;
    pieces[5].largeur = 1;
    pieces[5].forme[3] = "l";
    pieces[5].forme[2] = "l";
    pieces[5].forme[1] = "l";
    pieces[5].forme[0] = "l";
    pieces[6].hauteur = 1;
    pieces[6].largeur = 4;
    pieces[6].forme[0] = "llll";

    // Ajout des rotations
    pieces[0].rotG = &pieces[0];
    pieces[0].rotD = &pieces[0];

    pieces[1].rotG = &pieces[4];
    pieces[1].rotD = &pieces[3];
    pieces[2].rotG = &pieces[3];
    pieces[2].rotD = &pieces[4];
    pieces[3].rotG = &pieces[1];
    pieces[3].rotD = &pieces[2];
    pieces[4].rotG = &pieces[2];
    pieces[4].rotD = &pieces[1];

    pieces[5].rotG = &pieces[6];
    pieces[5].rotD = &pieces[6];
    pieces[6].rotG = &pieces[5];
    pieces[6].rotD = &pieces[5];
}

void affichePiece(Piece piece) {
    for (int i = piece.hauteur - 1; i >= 0; i--) // Pour chaque ligne de la forme de la pièce
        printf("%s\n", piece.forme[i]);
    printf("↑\n");
}

void ecrirePiece(Grille grille, Piece piece, int colonne, int hauteur) {
    if ((piece.largeur + colonne <= LARGEUR) &&
        (piece.hauteur + hauteur <= HAUTEUR)) { // Si les coordonnées sont dans la grille
        for (int i = 0; i < piece.hauteur; ++i) {
            for (int j = 0; j < piece.largeur; ++j) {
                if (piece.forme[i][j] != ' ') // Si la case de la forme n'est pas un espace
                    ecrireCase(grille, hauteur + i, colonne + j, piece.forme[i][j]);
            }
        }
    } else {
        printf("Impossible d'écrire la pièce ici (%d,%d)\n", colonne, hauteur);
    }
}

Piece pieceAleatoire(Piece pieces[NB_PIECES]) {
    //srand(time(0)); // Fait commencer la suite aléatoire a partir de l'heure système
    int alea = (int) (((double) rand() / ((double) RAND_MAX)) * (NB_PIECES));
    return pieces[alea];
}