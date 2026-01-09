#ifndef _JEU_H_
#define _JEU_H_
#include<stdio.h>
#include<stdlib.h>
#define N 30

typedef struct {
    int x; /*coordonnée x de la matrice */
    int y; /*coordonnée y de la matrice */
    int forme[4][4]; /*une matrice 4*4 qui représente la pièce */
}piece;

typedef struct{
    int tab[N][N]; /* tableau d'entier de taille N*N */
}grille;



grille cree_plateau(int n,int m);
void afficher_plateau(grille *g,int n,int m);
piece generer_piece_aleatoire();
void afficher_piece(piece *p);
int inserer_piece_grille(grille *g, piece *p);
int verification_colision_vertical(grille *g,piece *p,int x_plateau);
int descendre_verticalement_piece(grille *g,piece *p,int x_plateau);
int verification_colision_horizontale(grille *g, piece *p,int y_plateau,
                                      char direction);
void deplacement_droite_gauche__piece(grille *g, piece *p, int y_plateau,
                                      char direction);
void rotation_gauche(piece *p, piece *p2);
void rotation_droite(piece *p, piece *p2);
void deplacement_rotation(grille *g, piece *p, piece *p2,int x_plateau,int y_plateau, char direction);
int ligne_complete(grille *g, int x, int largeur_grille);
void enleve_ligne(grille *g, int x, int largeur_grille);
int verification_ligne(grille *g, int hauteur_grille,int largeur_grille);

#endif /* _JEU_H_ */

