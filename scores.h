#ifndef _SCORES_H_
#define _SCORES_H_

#define N_SCORES 11

/* Fonction remplissant un tableau utilisé pour la gestion des meilleurs scores à partir d'un fichier les contenants, renvoit la taille du tableau */

int remplir_tab(int tab[]);

 /* Affiche le tableau des scores, temporaire et inutile pour le jeu en lui-même */

void tmp_afficher_tab(int tab[], int n);

/* Tri le tableau dans un ordre décroissant */

void tri_bulles(int tab[], int n);

/* Fonction écrivant un nouveau scores dans le fichier des scores à partir du tableau de scores, gère les problèmes éventuels (plus de 10 scores, tri etc) renvoit 0 si tout c'est bien passé 0 sinon */

int ecrire_score(int score);

#endif /* _SCORES_H_ */