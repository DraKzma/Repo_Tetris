#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include <string.h>
#include "scores.h"

/* Fonction remplissant un tableau utilisé pour la gestion des meilleurs scores à partir d'un fichier les contenants */

int remplir_tab(int tab[]){

    /* déclaration des variables */
    
    FILE* fichier = NULL;
    int nb;
    int i = 0;

    /* ouverture du fichier en lecture */
    
    fichier=fopen("scores.txt", "r");
    if (fichier==NULL){
        printf("Vous tentez d'ouvrir un fichier inexsistant\n");
        return -1;
    }

    /* replissage du tableau des scores à partir des scores lus dans le fichier */
    
    while (fscanf(fichier, "%d", &nb) == 1){
        tab[i]=nb;
        i++;
    }

    /* fermeture du fichier */
    
    fclose(fichier);
    return i;
}

/* Affiche le tableau des scores, temporaire et inutile pour le jeu en lui-même */

void tmp_afficher_tab(int tab[], int n){

    /* déclaration des variables */
    
    int i;

    /* boucle d'affichage */
    
    for (i=0; i<n; i++){
        printf("%d\n",tab[i]);
    }
}

/* Tri le tableau dans un ordre décroissant */

void tri_bulles(int tab[], int n){

    /* déclaration des variables */
    
    int i, j, tmp;

    /* boucle de tri du tableau des scores */
    
    for (i=n-1; i>0; i--){
        for (j=0; j<i; j++){
            if (tab[j+1] > tab[j]){
                tmp=tab[j];
                tab[j]=tab[j+1];
                tab[j+1]=tmp;
            }
        }
    }
}

/* Fonction écrivant un nouveau scores dans le fichier des scores à partir du tableau de scores, gère les problèmes éventuels (plus de 10 scores, tri etc) */

int ecrire_score(int score){

    /* déclaration des variables */
    
    int tab[N_SCORES];
    int n, i;
    FILE* fichier = NULL;

    /* appel de la fonction remplir_tab pour remplir le tableau des scores */
    
    n=remplir_tab(tab);

    /* affecte la dernière case du tableau du score que l'on veut insérer */
    
    tab[n]=score;

    /* augmentation de la taille du tableau des scores pour le tri uniquement */
    
    n+=1;

    /* tri du tableau des scores */
    
    tri_bulles(tab, n);

    /* ouverture du fichier des scores en écriture */
    
    fichier=fopen("scores.txt", "w");
    if (fichier==NULL){
        printf("Impossible d'ouvrir le fichier\n");
        return -1;
    }

    /* boucle qui écrit le tableau des scores dans le fichier des scores */
    
    for (i=0; i<n-1; i++){
        fprintf(fichier, "%d\n", tab[i]);
    }

    /* fermeture du fichier des scores */
    
    fclose(fichier);
    return 0;
}

    
    
