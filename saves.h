#ifndef _SAVES_H_
#define _SAVES_H_

#include "jeu.h"

/* structure partie contenant un plateau, un bloc principal, un bloc suivant et un score UTILISEE UNIQUEMENT POUR LES SAUVEGARDES */

typedef struct {
    grille plateau;
    piece piece_principale;
    piece piece_suivante;
    int score;
    int vitesse;
    float temps;
} partie;

/* définition d'un tableau de 4 parties */

typedef partie tab_parties[4];

/* fonction temporaire qui remplit le fichier des sauvegardes avec 4 sauvegardes nulles (NECESSAIRE AU BON FONCTIONNEMENT DES FONCTIONS QUI SUIVENT) */

int tmp_remplir_fichier_saves();

/* fonction qui remplit un tableau de 4 sauvegardes à partir du fichier de sauvegarde */

int remplir_tab_saves(tab_parties t);

/* fonction temporaire qui affiche le plateau des quatres sauvegardes de t */

void tmp_afficher_plateau_saves(tab_parties t);

/* fonction qui convertie la partie en cours en partie à sauvegarder */

void en_cours_to_save(partie* p, grille t, piece piece_principale, piece piece_suivante, int score, int vitesse, float temps);

/* fonction qui convertie la partie sauvegardée en partie en cours (chargement de partie) */

void save_to_en_cours(partie p, grille* t, piece* piece_principale, piece* piece_suivante, int* score, int* vitesse, float* temps);

/* fonction qui sauvegarde une partie dans le fichier de sauvegarde à l'emplacement x */

int ecrire_save(grille t, piece piece_principale, piece piece_suivante, int score, int vitesse, float temps, int x);

/* fonction qui charge la partie x */

void load_partie(grille* t, piece* piece_principale, piece* piece_suivante, int* score, int* vitesse, float* temps, int x);

#endif /* _SAVES_H_ */