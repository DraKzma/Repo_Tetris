#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "saves.h"

/* fonction temporaire qui remplit le fichier des sauvegardes avec 4 sauvegardes nulles (NECESSAIRE AU BON FONCTIONNEMENT DES FONCTIONS QUI SUIVENT) */

int tmp_remplir_fichier_saves(){

    /* déclaration des variables */
    
    FILE* fichier=NULL;
    int i,j, n;
    float tmp;

    /* ouverture du fichier de sauvegarde */
    
    fichier=fopen("saves.txt", "w");
    if (fichier==NULL){
        printf("Fichier inexsistant\n");
        return -1;
    }
    /* initialisation de certaines variables pour les boucles */
    
    i=0; /* i varie de 0 à 3 */
    n=0; /* n est une constante qu'on écrit dans le fichier */
    tmp=0; /* constante float */

    /* boucle qui écrit dans le fichier de sauvegarde (QUATRE SAUVEGARDES) */
    
    while(i!=4){

        /* sous boucle qui écrit le plateau principal de chaque sauvegarde */
        
        for(j=0; j<200; j++){
            fprintf(fichier, "%d ", n);
        }

        /* sous boucle qui écrit les coordonnées du bloc principal */
        
        for (j=0; j<2; j++){
            fprintf(fichier, "%d ", n);
        }

        /* sous boucle qui écrit la sous matrice du bloc principal */
        
        for (j=0; j<16; j++){
            fprintf(fichier, "%d ", n);
        }

        /* sous boucle qui écrit les coordonnées du bloc suivant */
        
        for (j=0; j<2; j++){
            fprintf(fichier, "%d ", n);
        }

        /* sous boucle qui écrit la sous matrice du bloc suivant */
        
        for (j=0; j<16; j++){
            fprintf(fichier, "%d ", n);
        }

        /* écriture du score, saut de ligne et incrémentation de i (=ON PASSE A LA PROCHAINE SAUVEGARDE) */
        
        fprintf(fichier, "%d ", n);
        fprintf(fichier, "%d ", n);
        fprintf(fichier, "%f\n", tmp);
        i++;
    }

    /* fermeture du fichier de sauvegarde */
    
    fclose(fichier);
    return 0;  
}

/* fonction qui remplit un tableau de 4 sauvegardes à partir du fichier de sauvegarde */

int remplir_tab_saves(tab_parties t){

    /* déclaration des variables */
    
    FILE* fichier=NULL;
    int i, j, n;

    /* initialisation de la variable de la boucle principale */
    
    n=0; /* n varie de 0 à 3 (QUATRE SAUVEGARDES) */

    /* ouverture du fichier de sauvegarde en lecture */
    
    fichier=fopen("saves.txt", "r");
    if (fichier==NULL){
        printf("Fichier inexsistant\n");
        return -1;
    }

    /* boucle qui lit dans le fichier de sauvegarde */
    
    while(n!=4){

        /* sous boucle qui lit le plateau principal pour chaque sauvegarde */
        
        for (i=0; i<20; i++){
            for (j=0; j<10; j++){
                if (fscanf(fichier, "%d", &t[n].plateau.tab[i][j])!=1){
                        printf("Erreur de lecture\n");
                        return -1;
                }
            }
        }

        /* sous boucle qui lit les coordonnées du bloc principal */

        for (i=0; i<2; i++){
            if (i==0){
                if (fscanf(fichier, "%d", &t[n].piece_principale.x)!=1){
                    printf("Erreur de lecture\n");
                    return -1;
                    }
                else{
                    if (fscanf(fichier, "%d", &t[n].piece_principale.y)!=1){
                        printf("Erreur de lecture\n");
                        return -1;
                    }
                }
            }
        }

        /* sous boucle qui lit la sous matrice du bloc principal */
        
        for (i=0; i<4; i++){
            for (j=0; j<4; j++){
                if (fscanf(fichier, "%d", &t[n].piece_principale.forme[i][j])!=1){
                        printf("Erreur de lecture\n");
                        return -1;
                }
            }
        }

        /* sous boucle qui lit les coordonnées du bloc suivant */
        
        for (i=0; i<2; i++){
            if (i==0){
                if (fscanf(fichier, "%d", &t[n].piece_suivante.x)!=1){
                    printf("Erreur de lecture\n");
                    return -1;
                    }
                else{
                    if (fscanf(fichier, "%d", &t[n].piece_suivante.y)!=1){
                        printf("Erreur de lecture\n");
                        return -1;
                    }
                }
            }
        }

        /* sous boucle qui lit la sous matrice du bloc suivant */
        
        for (i=0; i<4; i++){
            for (j=0; j<4; j++){
                if (fscanf(fichier, "%d", &t[n].piece_suivante.forme[i][j])!=1){
                        printf("Erreur de lecture\n");
                        return -1;
                }
            }
        }

        /* lecture du score, de la vitesse et du temps et incrémentation de n (=ON PASSE A LA SAUVEGARDE SUIVANTE */
        
        if (fscanf(fichier, "%d", &t[n].score)!=1){
                        printf("Erreur de lecture\n");
                        return -1;
        }
        if (fscanf(fichier, "%d", &t[n].vitesse)!=1){
            printf("Erreur de lecture\n");
            return -1;
        }
        if (fscanf(fichier, "%f", &t[n].temps)!=1){
            printf("Erreur de lecture\n");
            return -1;
        }
        n++;
    }
    return 0;
}

/* fonction temporaire qui affiche le plateau des quatres sauvegardes de t */

void tmp_afficher_plateau_saves(tab_parties t){

    /* déclaration des variables */
    
    int i, j, n;

    /* initialisation de la variable de la boucle principale */
    
    n=0; /* n varie de 0 à 3 (QUATRE SAUVEGARDES) */

    /* boucle affichant le tableau des sauvegardes */
    
    while(n!=4){
        for (i=0; i<20; i++){
            for (j=0; j<10; j++){
                printf("%d ", t[n].plateau.tab[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        n++;
    }
}

/* fonction qui convertie la partie en cours en partie à sauvegarder */

void en_cours_to_save(partie* p, grille t, piece piece_principale, piece piece_suivante, int score, int vitesse, float temps){

    /* déclaration des variables */
    
    int i,j;

    /* boucle qui affecte le plateau */
    
    for (i=0; i<20; i++){
        for (j=0; j<10; j++){
            p->plateau.tab[i][j]=t.tab[i][j];
        }
    }

    /* affectation des coordonnées de la pièce principale */
    
    p->piece_principale.x=piece_principale.x;
    p->piece_principale.y=piece_principale.y;

    /* boucle qui affecte la sous matrice de la pièce principale */
    
    for (i=0; i<4; i++){
        for (j=0; j<4; j++){
            p->piece_principale.forme[i][j]=piece_principale.forme[i][j];
        }
    }

    /* affectation des coordonnées de la pièce suivante */
    
    p->piece_suivante.x=piece_suivante.x;
    p->piece_suivante.y=piece_suivante.y;

    /* boucle qui affecte la sous matrice de la pièce suivante */
    
    for (i=0; i<4; i++){
        for (j=0; j<4; j++){
            p->piece_suivante.forme[i][j]=piece_suivante.forme[i][j];
        }
    }

    /* affectation du score */
    
    p->score=score;
    p->vitesse=vitesse;
    p->temps=temps;
}

/* fonction qui convertie la partie sauvegardée en partie en cours (chargement de partie) */

void save_to_en_cours(partie p, grille* t, piece* piece_principale, piece* piece_suivante, int* score, int* vitesse, float* temps){

    /* déclaration des variables */
    
    int i,j;

    /* boucle qui affecte le plateau de jeu */
    
    for (i=0; i<20; i++){
        for (j=0; j<10; j++){
            t->tab[i][j]=p.plateau.tab[i][j];
        }
    }

    /* affectation des coordonnées de la pièce principale */
    
    piece_principale->x=p.piece_principale.x;
    piece_principale->y=p.piece_principale.y;

    /* boucle qui affecte la sous matrice de la pièce principales */
    
    for (i=0; i<4; i++){
        for (j=0; j<4; j++){
        piece_principale->forme[i][j]=p.piece_principale.forme[i][j];
        }
    }

    /* afffectation des coordonnées de la pièce suivante */
    
    piece_suivante->x=p.piece_suivante.x;
    piece_suivante->y=p.piece_suivante.y;

    /* boucle qui affecte la sous matrice du bloc suivant */
    
    for (i=0; i<4; i++){
        for (j=0; j<4; j++){
        piece_suivante->forme[i][j]=p.piece_suivante.forme[i][j];
        }
    }

    /* affectation du score */
    
    *score=p.score;
    *vitesse=p.vitesse;
    *temps=p.temps;
}

/* fonction qui sauvegarde une partie dans le fichier de sauvegarde à l'emplacement x */

int ecrire_save(grille t, piece piece_principale, piece piece_suivante, int score, int vitesse, float temps, int x){

    /* déclaration des variables */
    
    tab_parties tab_p;
    FILE* fichier=NULL;
    int i,j,n;

    /* remplissage du tableau des sauvegardes à partir du fichier de sauvegarde */
    
    remplir_tab_saves(tab_p);

    /* replacement de la sauvegarde x par la partie en cours dans le tableau */
    
    en_cours_to_save(&(tab_p[x]), t, piece_principale, piece_suivante, score, vitesse, temps);

    /* affichage temporaire A SUPPRIMER
    
    tmp_afficher_plateau_saves(tab_p);

    */

    /* ouverture du ficher de sauvegarde */
    
    fichier=fopen("saves.txt", "w");
    if (fichier==NULL){
        printf("Fichier inexsistant\n");
        return -1;
    }

    /* initialisation de la variable de la boucle principale */
    
    n=0; /* n varie de 0 à 3 (QUATRE SAUVEGARDES) */

    /* boucle qui écrit le nouveau tableau des sauvegardes dans le fichier de sauvegarde */
    
    while(n!=4){

        /* sous boucle écrivant le plateau de chaque sauvegarde */
        
        for (i=0; i<20; i++){
            for (j=0; j<10; j++){
                fprintf(fichier, "%d ", tab_p[n].plateau.tab[i][j]);
            }
        }

        /* écriture des coordonnées de la pièce principale */
        
        fprintf(fichier, "%d ", tab_p[n].piece_principale.x);
        fprintf(fichier, "%d ", tab_p[n].piece_principale.y);

        /* sous boucle écrivant la sous matrice du bloc principal */
        
        for (i=0; i<4; i++){
            for (j=0; j<4; j++){
                fprintf(fichier, "%d ", tab_p[n].piece_principale.forme[i][j]);
            }
        }

        /* écriture des coordonnées du bloc suivant */
        
        fprintf(fichier, "%d ", tab_p[n].piece_suivante.x);
        fprintf(fichier, "%d ", tab_p[n].piece_suivante.y);

        /* sous boucle écrivant la sous matrice du bloc suivant */
        
        for (i=0; i<4; i++){
            for (j=0; j<4; j++){
                fprintf(fichier, "%d ", tab_p[n].piece_suivante.forme[i][j]);
            }
        }

        /* écriture du score, de la vitesse et du temps et incrémentation de n (=PASSER A LA SAUVEGARDE SUIVANTE) */
        
        fprintf(fichier, "%d ", tab_p[n].score);
        fprintf(fichier, "%d ", tab_p[n].vitesse);
        fprintf(fichier, "%f\n", tab_p[n].temps);
        n++;
    }

    /* fermerture du fichier */
    
    fclose(fichier);
    return 0;
}

/* fonction qui charge la partie x */

void load_partie(grille* t, piece* piece_principale, piece* piece_suivante, int* score, int* vitesse, float* temps, int x){

    /* déclaration des variables */

    tab_parties tab_p;

    /* remplissage du tableau des sauvegardes à partir du fichier de sauvegarde */
    
    remplir_tab_saves(tab_p);

    /* affichage temporaire des plateaux du tableau des sauvegardes
    
    tmp_afficher_plateau_saves(tab_p);

    */

    /* conversion de la sauvegarde x en partie en cours A PARTIR DES ADRESSES (=CHANGEMENT IMMEDIAT) */
    
    save_to_en_cours(tab_p[x], t, piece_principale, piece_suivante, score, vitesse, temps);
}




