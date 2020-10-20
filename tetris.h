#ifndef TP3_TETRIS_H
#define TP3_TETRIS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Définition des constantes
#define HAUTEUR 10
#define LARGEUR 15
#define NB_PIECES 7
#define HAUTEUR_MAX_DES_PIECES 4

// Définition des structures de données
struct SPiece {
    int hauteur;
    int largeur;
    char *forme[HAUTEUR_MAX_DES_PIECES];
    struct SPiece* rotG;
    struct SPiece* rotD;
};
typedef struct SPiece Piece;

typedef char Grille[HAUTEUR][LARGEUR];

// Initialise la grille de jeu
void initialiseGrille(Grille grille);

// Renvoie le caractère à la position ligne,colonne dans la grille
char lireCase(Grille grille, int ligne, int colonne);

// Ecris dans la grille
void ecrireCase(Grille grille, int ligne, int colonne, char c);

// Affiche la grille
void afficheGrille(Grille grille);

// Renvoie la hauteur de la colonne la plus haute de la grille dans l'interval donné
int hauteurPlat(Grille grille, int debut, int fin);

// Renvoie la hauteur exacte ou peut aller la pièce
int hauteurExacte(Grille grille, int colonne, Piece piece);

// Supprime la ligne et descend toutes les lignes supérieures
void supprimerLigne(Grille grille, int ligne);

// Nettoie la grille de toutes les lignes pleines
int nettoyer(Grille grille);

// _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-.

// Initialise les pièces
void initialisePieces(Piece pieces[NB_PIECES]);

// Affiche la pièce avec une flèche en dessous
void affichePiece(Piece piece);

// Ecris la piece dans la grille à la colonne demandée
void ecrirePiece(Grille grille, Piece piece, int colonne, int hauteur);

// Tire une pièce aléatoirement dans le tableau de pièces
Piece pieceAleatoire(Piece pieces[NB_PIECES]);

#endif //TP3_TETRIS_H
