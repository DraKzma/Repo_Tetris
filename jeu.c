#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"jeu.h"
#include<unistd.h>


/* fonction qui renvoie un plateau de type grille(voir jeu.h) remplie de 0 de taille n par m */
grille cree_plateau(int n, int m){
    /* on crée une grille vierge */
    grille g;
    int i,j;
    /* parcours des lignes */
    for (i=0 ; i<n ; i++){
        /* parcours des colonnes */
        for (j=0 ; j<m ; j++){
            /* la case de coordonnée i j et initialisé à 0 */
            g.tab[i][j] = 0;
        }
    }
    /* renvoie de g */
    return g;
}

/*fonction qui permet d'afficher un plateau de type grille de taille n*m */
void afficher_plateau(grille *g , int n, int m){
    int i,j;
    /* parcours des lignes */
    for (i=0 ; i<n ; i++){
        /* parcours les colonnes */
        for (j=0; j<m ;j++){
            /* affichage de la case de coordonnée i j */
            printf("%d", g->tab[i][j]);
        }
        /* retour à la ligne lorsque une ligne se fini */
        printf("\n");
    }
}

/* cette fonction de type piece génère aléatoirement une piece, chaque piece contient une position x et une position y, il s'agit des coordonnées de la matrice 4*4 le plus en haut à gauche   */
piece generer_piece_aleatoire(){
    piece l[7]={
        /* représente les différentes formes, les 1 représentent les case occupé par le tétro et les 2 le restes des cases de la matrice */
        /* initilisation de du premier tétro ayant pour coordonnée 0 0 */
        /* coordonnée x et y désigne le point le plus en haut à gauche */
        {0,0,{{2,2,2,2},{1,1,1,1},{2,2,2,2},{2,2,2,2}}},  /*forme 1 */
        {0,0,{{2,2,2,2},{2,1,2,2},{2,1,1,1},{2,2,2,2}}},  /*forme 2 */
        {0,0,{{2,2,2,2},{2,2,1,2},{1,1,1,2},{2,2,2,2}}},  /*forme 3 */
        {0,0,{{2,2,2,2},{2,1,1,2},{2,1,1,2},{2,2,2,2}}},  /*forme 4 */
        {0,0,{{2,2,2,2},{2,1,1,2},{1,1,2,2},{2,2,2,2}}},  /*forme 5 */
        {0,0,{{2,2,2,2},{2,1,2,2},{1,1,1,2},{2,2,2,2}}},  /*forme 6 */
        {0,0,{{2,2,2,2},{2,1,1,2},{2,2,1,1},{2,2,2,2}}}   /*forme 7 */ 
    };
    int val;
    /* tirage aléatoirement d'une valeur comprise entre 0 et 6 */
    val = rand()%7;
    /* renvoie d'une pièce aléatoirement */
    return l[val];
}

/* fonction qui prend en paramètre une pièce et qui affiche la pièce(une matrice 4*4) */
void afficher_piece(piece *p){
    int i,j;
    /* parcours des 4 lignes */
    for (i=0 ; i<4 ; i++){
        /* parcours des 4 colonnes */
        for (j=0 ; j<4 ; j++){
            /* affichage de la case de coordonnée i j */
            printf("%d",p->forme[i][j]);
        }
        /* retour à la ligne car la ligne est fini */
        printf("\n");
    }
}

/* fonction prend en paramètre un pointeur vers une grille et un pointeur vers une piece p 
cette fonction insère la pièce dans la grille g tout en haut a gauche  */
/* lorsque on ne peut plus insérer de piece dans la grille alors cela signifie que l'on a perdu */
/* la fonction renvoie soit 20  lorsque l'on insert une nouvelle pièce et on gagne 20 points soit -1 si on ne peux pas insérer de nouvelle pièce */
int inserer_piece_grille(grille *g, piece *p){
    int i,j,r;
    /*initialisation de la variable r qui représente le retour de la fonction */
    r=20;
    /* cette boucle la vérifie si l'on peut insérer la pièce ou non, en vérifiant s'il y'a des 3 qui empêchent l'insertion de notre nouvelle pièce */
    for (i=0 ; i<4 ; i++){
        for (j=0 ; j<4 ; j++){
            if (g->tab[i][j] == 3 && p->forme[i][j] == 1){
                r = -1;
            }
        }
    }
    /* cette condition là est éxécuté uniquement si le test précédent n'a pas modifié la valeur de r. Dans ce cas là, alors on insert la pièce */
    if (r != -1){
        for (i=0 ; i<4 ; i++){
            for (j=0 ; j<4 ; j++){
                /* condition qui regarde s'il y'a des 3, car puisque la pièce est de taille 4*4, et que la pièce est formé de 2 et de 1 alors il peut y avoir des 3 qui ne gènent pas l'insertion de la pièce mais qui sont présent à l'endroit où l'on veut copié la matrice. il ne faut alors pas les remplacés par des 2 car les 3 désigne des pièces fixe. */
                if (g->tab[i][j] != 3){
                    /* copie de la pièce dans la grille*/
                    g->tab[i][j] = p->forme[i][j];
                }
            }
        }
    }
    /* renvoie soit 20 si la pièce c'est bien insérée soit -1 car il y'a eu un problème dans l'insertion */
    return r;
}

/* fonction qui prend en paramètre un pointeur vers une grille g et un pointeur vers une pièce p, elle fige la pièce dans la grille c'est à dire que elle transforme tous les 1 de la matrice en 3, elle ne renvoie rien */
void fige_piece(grille *g, piece *p){
    int i,j;
    /* boucle qui parcours la pièce de taille 4*4 */
    for (i=0 ; i<4 ; i++){
        for (j=0 ; j<4 ; j++){
            /* transformation des 1 en 3*/
            if (g->tab[i+p->x][j+p->y] == 1){
                g->tab[i+p->x][j+p->y] = 3;
            }
            else{
                /* les 2 sont remplacés par des des 0, on fait attention que la case de coordonée x y ne soit pas un 3 car celà désigne un bloc figé */
                if (g->tab[i+p->x][j+p->y] != 3){
                    
                    g->tab[i+p->x][j+p->y] = 0;
                }
            }
        }
    }
}


/* fonction colision qui prend en argument un pointeur vers la grille g, un 
pointeur vers une piece p, la taille x du plateau et renvoie 1 s'il y'a une colision avec une autre pièce ou s'il y'a colision avec la bordure du plateau et renvoie -1 s'il n'y a pas de colision
 */
int verification_colision_vertical(grille *g, piece *p,int x_plateau){
    int i, j, r=-1; /* de base, on initialise r à -1 car il n'y a pas de colisions */
    /* parcours pour une matrice 4*4 */
    for (i=0 ; i<4 ; i++){
        for (j=0 ; j<4 ; j++){
            /* si la case i j vaut 1 c'est à dire si la case est un bloc */
            if (p->forme[i][j] == 1){
                /* alors on regarde si la case d'absice x+1 est déjà occupé ou non ou non */
                if (g -> tab[i+p->x+1][j+p->y] == 3){
                    r = 1; /* la piece touche une autre piece, on renvoie 1 */
                    /* on fige la pièce car lorsque la pièce touche une autre pièce lorsque elle descend vers le bas alors elle est figé */
                    fige_piece(g,p);
                }
                /* on regarde si la case d'absice x+1 touche la bordure basse du plateau */
                if (i+p->x+1 >= x_plateau){
                    r = 1; /*la piece touche la bordure basse de la grille */
                    /* on fige la pièce car lorsque la pièce touche la bordure basse alors elle est figé*/
                    fige_piece(g,p);
                }
            }
        }
    }
    /* renvoie soit 1(il y'a colision) soit -1( il n'y a pas de colision) */
    return r; 
}


/* fonction qui prend en argument un pointeur vers une grille g, un pointeur vers une piece p, la coordonnée x du plateau(sa hauteur, par défaut 20), et modifie la grille avec la piece p qui est descendu de 1 absice s'il n'y a pas de colission avec la bordure ou d'autre pièce. elle renvoie -1 si le déplacement s'est déroulé correctement et 1 sinon
on ne fait pas une fonction void car le retour de la pièce est utilisé pour savoir si l'on doit ou non générer une nouvelle pièce. */
int descendre_verticalement_piece(grille *g, piece *p, int x_plateau){
    int i,j,r;
    r=-1; /* on initialise r à -1 */
    /* on test si le déplacement est possible */
    if (verification_colision_vertical(g,p,x_plateau) == -1){
        /* parcours de la pièce */
        for(i=0 ; i<4 ; i++){
            for (j=0 ; j<4 ; j++){
                /* s'il n'y a pas déjà une pièce figé alors on met l'ensemble des blocs à 0 */
                if (g->tab[i+p->x][j+p->y] != 3){ 

                    g->tab[i+p->x][j+p->y] = 0;
                }
            }
        }
        /* recopie de la pièce au avec le déplacement vertical c'est à dire que chaque bloc à pour coordonnée en absice x+1 */
        for (i=0 ; i<4 ; i++){
            for (j=0 ; j<4 ; j++){
                if(g->tab[i+p->x+1][j+p->y] != 3){
                    g->tab[i+p->x+1][j+p->y] = p->forme[i][j];
                }
            }
        }
        /* modification des coordonnées, la coordonnée x de la matrice pièce est augmenter de 1 (pour rappel, la coordonnée x de la matrice pièce est la coordonnée tout en haut
           à gauche, c'est à dire le point 0 0 */
        p->x+=1;           
    }
    /* si la pièce ne peut pas être déplacée alors on met r à 1 c'est à dire qu'il y'a eu un soucis dans le déplacement de la pièce*/
    else{
        if (verification_colision_vertical(g,p,x_plateau == 1)){
                r = 1;
        }

    }
    /* renvoie de r */
    return r;
}


/* fonction qui prend en argument un pointeur vers une grille g,un pointeur vers une pièce p, la coord y du plateau (sa largeur par défaut 10),une direction, et renvoie -1 s'il n'y a pas de colision et 1 si il y'a colision avec la bordure*/
int verification_colision_horizontale(grille *g, piece *p,int y_plateau,char direction){
    int i, j, r=-1; /* par défaut, il n'y a pas de colision */
    /* parcours des coordonnées de la pièce */
    for (i=0 ; i<4 ; i++){
        for (j=0 ; j<4 ; j++){
            /* si il s'agit d'un bloc et non pas d'une case vide */
            if (p->forme[i][j] == 1){
                /* on regarde la direction, d pour droite, et g pour gauche */
                if (direction == 'd'){
                    
                    if ((g->tab[i+p->x][j+p->y+1] == 3) ||(j+p->y+1 >= y_plateau)){
                        r = 1; /* la piece touche une autre piece ou la bordure, on met r à 1 */
                    }
                }
                if (direction == 'g'){
                    if ((g->tab[i+p->x][j+p->y-1] == 3) || (j+p->y-1 < 0)){
                        r = 1; /* la piece touche une autre piece ou la bordure, on met r à 1 */
                    }
                }
            }
        }
    }
    /* renvoie r, soit 1 soit -1*/
    return r; 

}

/*fonction qui prend en paramètre un pointeur vers une grille g, un pointeur vers une piece p, une coordonnée y de plateau(sa largeur), et une direction, soit le caractère d pour droite soit le caractère g pour gauche.
elle renvoie la grille avec la modification attendu donc soit un déplacement de la pièce vers la gauche soit un déplacement de la pièce vers la droite.
cette fois ci, il s'agit d'une fonction void car on ne pourra pas*/
void deplacement_droite_gauche__piece(grille *g, piece *p, int y_plateau,char direction){
    int i,j;
    int val_dir = 0; /* par défaut, on met à 0 */
    /* s'il n'y a pas de colision alors */
    if (verification_colision_horizontale(g,p,y_plateau,direction) == -1){
        /* on fait un switch sur direction, et on met val_dir à -1 si la direction vaut g(pour gauche) et val_dir à 1 si la direction vaut d(pour droite) */
        switch(direction){
        case 'g' :
            val_dir = -1;
            break;
        case 'd' :
            val_dir = 1;
            break;
        }
        /* parcours de la pièce */
        for(i= 0; i<4 ; i++){
            for (j=0 ; j<4 ; j++){
                /*s'il n'y a pas déjà une pièce figé alors on met l'ensemble des blocs à 0 */
                if (g->tab[i+p->x][j+p->y] != 3){ 
                    g->tab[i+p->x][j+p->y] = 0;
                }
            }
        }
        /* recopie de la pièce avec le déplacement adéquat */
        for (i=0 ; i<4 ; i++){
            for (j=0 ; j<4 ; j++){
                if (g->tab[i+p->x][j+p->y+val_dir] != 3){
                    g->tab[i+p->x][j+p->y+val_dir] = p->forme[i][j];
                }
            }
        }
        /* modification de y, soit on le décrémente de 1 soit on l'incrémente de 1*/
        p->y+=val_dir;
    }
}



/* fonction rotation qui prend 2 pointeurs vers 2 pièces, l'original et une vierge qui sera une copie de la première avec la rotation réalisé */
void rotation_gauche(piece *p,piece *p2){
    int i,j;
    /* recopie de piece p dans pièce p2 */ 
    p2->x = p->x;
    p2->y = p->y;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            /* formule de rotation d'une pièce */
            p2->forme[i][j] = p->forme[j][3 - i];  
        }
    }
}

void rotation_droite(piece *p, piece *p2){
    int i,j;
    /* recopie de piece p dans pièce p2 */ 
    p2->x = p->x;
    p2->y = p->y;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            /* formule de rotation d'une pièce */
            p2->forme[i][j] = p->forme[3-j][i];  
        }
    }
}
    
    

/* fonction qui realise la rotation vers la gauche en vérifiant les colisions, elle prend en paramètre un pointeur vers une grille g, un pointeur vers une piece p, un pointeur vers une piece p2, un entier qui représente la hauteur du plateau */

void deplacement_rotation(grille *g, piece *p,piece *p2,int x_plateau, int y_plateau, char direction){
    int i,j;
    int r = -1; /* de base il n'y a pas de colision */
    if (direction == 'd'){
        rotation_droite(p,p2);/* appel de la fonction rotation */
    }
    if (direction == 'g'){
        rotation_gauche(p,p2);
    }
    for (i=0; i<4; i++){
        for (j=0 ; j<4 ; j++){
            /* si la rotation ne peut pas être réalisé car un bloc figé gène la rotation */
            if (p2->forme[i][j] == 1 && g->tab[p2->x+i][p2->y+j] == 3){
                r = 1;
            }
            /* si on ne peut pas éffectuer la rotation car la rotation sort des limites du plateau en absice */
            if (p2->forme[i][j] == 1 && i+p2->x >= x_plateau){
                r = 1;
            }
            /* si on ne peut pas éffectuer la rotation car la rotation sort des limites du plateau en ordonnée(vers la droite)*/
            if (p2->forme[i][j] == 1 && j+p2->y >= y_plateau){
                r = 1;
            }
            /* si on ne peut pas éffectuer la rotation car la rotation sort des limites du plateau en ordonnée(vers la gauche)*/

            if (p2->forme[i][j] == 1 && j+p2->y < 0){
                r = 1;
            }
        }
    }
    /* s'il n'y a pas de colision alors */
    if (r == -1){
        /* effacement de l'ancienne pièce */
        for (i=0 ; i<4 ; i++){
            for (j=0; j<4 ; j++){
                if (g->tab[i+p->x][j+p->y] != 3){ 

                    g->tab[i+p->x][j+p->y] = 0;
                }
            }
        }
                
        /* recopie de la nouvelle */
        for (i=0 ; i<4 ; i++){
            for (j=0 ; j<4 ; j++){
                /* recopie de la copie dans la pièce principal */
                p->forme[i][j]=p2->forme[i][j];
                /* si il n'y pas de bloc figé alors on recopie la matrice ( ce cas la est différent des précédents car c'est pour ne pas écraser des blocs figés par des 2*/
                if (g->tab[i+p2->x][j+p2->y] != 3){
                    g->tab[i+p2->x][j+p2->y] = p2->forme[i][j];
                }
            }
        }
    }
}

/* fonction qui renvoie -1 si la ligne x ne contient pas que des 3 et sinon renvoie 1 */
int ligne_complete(grille *g, int x, int largeur_grille){
    int j;
    int r;
    r = 1; /* de base on part du principe que il y'a que des 3 et dès qu'on trouve que la case de coordonnée i j n'est pas un 3 alors on met r à -1*/
    for (j=0; j < largeur_grille ; j++){
        if ( g->tab[x][j] != 3){
            r = -1;
        }
    }
    return r;
}

/* la fonction enleve ligne prend en paramètre un pointeur vers une grille, un entier x qui représente la ligne et renvoie la grille en supprimant la ligne x en décalant toutes les lignes qui sont au dessus de la ligne x vers le bas et en mettant la première ligne à 0 */ 

void enleve_ligne(grille *g, int x, int largeur_grille){
    int i,j;
    /* on recopie la ligne du dessus pour les lignes allant de la ligne x à la 
       ligne 1 */
    for (i=x ; i>0 ; i--){
        for (j=0 ; j<largeur_grille ; j++){
            g->tab[i][j] = g->tab[i-1][j];
        }
    }
    /* mettre la première ligne à 0 */
    for (j=0 ; j<largeur_grille ; j++){
        g->tab[0][j] = 0;
    }
}

/* fonction qui prend en argument un pointeur vers la grille et un entier qui représente la hauteur de la grille et renvoie le score, +50 pour chaque ligne écrasé */

int verification_ligne(grille *g, int hauteur_grille, int largeur_grille){
    int i;
    int score = 0;
    /* parcours des lignes */
    for (i=0 ; i<hauteur_grille ; i++){
        /* pour chaque ligne on test si elle est remplie de 3 */
        if (ligne_complete(g, i, largeur_grille) ==1){
            /* si elle est remplie de 3 on appel la fonction enleve ligne */
            enleve_ligne(g, i, largeur_grille);
            score += 50;
        }
    }
    /*renvoie du score, soit 0 soit le nombre de ligne remplacé * 50 */
    return score;
}
            
/*

int main(){
    int i=1;
    grille plat;
    piece tetro;
    piece tetro2; utiliser pour rotation
    plat=cree_plateau(20,10);
     srand(time(NULL));
    tetro=generer_piece_aleatoire();
    printf("\n");
    afficher_plateau(&plat,20,10);
    printf("\n");
    inserer_piece_grille(&plat,&tetro);
    while (i==1){
        printf("\n");
        if (descendre_verticalement_piece(&plat,&tetro,20)==1){
            tetro=generer_piece_aleatoire();
            if (inserer_piece_grille(&plat,&tetro) == -1){
                printf("vous avez perdu ! ");
                printf("\n");
                i=0;
            }
        }
        afficher_plateau(&plat,20,10);
    }
    printf("\n");
    printf("\n");
    deplacement_rotation(&plat,&tetro,&tetro2);
    afficher_plateau(&plat,20,10); */
    /*printf("\n");
    printf("%d %d \n",tetro.x,tetro.y);
    exit(EXIT_SUCCESS);

}
*/

/* 
 if (descendre_verticalement_piece(&plat,&tetro,20)==1){
            tetro=generer_piece_aleatoire();
            inserer_piece_grille(&plat,&tetro); */
/* ca genere des nouvelles pièces*/