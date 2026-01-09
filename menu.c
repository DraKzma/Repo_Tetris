#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include <time.h>
#include "scores.h"
#include "saves.h"
#define TAILLE_CHAINE 5
#define TAILLE_TEMPS 10

/* fonction générant le menu principal du jeu */

void generer_menu(MLV_Font* font_title_menu, MLV_Font* font_text_menu, MLV_Font* font_cross_menu){

    MLV_clear_window(MLV_COLOR_BLACK);

    /* génère les 4 boutons principaux */
    
    MLV_draw_rectangle(600, 400, 300, 100, MLV_COLOR_WHITE);
    MLV_draw_rectangle(600, 550, 300, 100, MLV_COLOR_WHITE);
    MLV_draw_rectangle(600, 700, 300, 100, MLV_COLOR_WHITE);
    MLV_draw_rectangle(600, 850, 300, 100, MLV_COLOR_WHITE);

    /* création du bouton quitter */
    
    MLV_draw_filled_rectangle(1450, 0, 50, 50, MLV_COLOR_RED);

    /* affiche les textes */
    
    MLV_draw_text_with_font(400, 100, "T3triX", font_title_menu, MLV_COLOR_RED);
    MLV_draw_text_with_font(700, 430, "Play", font_text_menu, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(690, 580, "Save", font_text_menu, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(690, 730, "Load", font_text_menu, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(675, 880, "Scores", font_text_menu, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(1460, 0, "X", font_cross_menu, MLV_COLOR_WHITE);

    /* actualise la fenêtre */
    
    MLV_actualise_window();
}

/* fonction générant le jeu en lui-même */

void generer_jeu(MLV_Font* font_cross_play, MLV_Font* font_arrow_play, MLV_Font* font_text_play, MLV_Font* font_score_play, grille plateau, piece piece_suivante, int score_en_cours, float temps_en_cours){

    int i, j;
    char chaine_score[TAILLE_CHAINE];
    char chaine_temps[TAILLE_TEMPS];
    MLV_clear_window(MLV_COLOR_BLACK);

    /* boucle générant la grille de jeu */
    
    for (i=0; i<=19; i++){
        for (j=0; j<=9; j++){
            MLV_draw_rectangle(500+(j*50), i*50, 50, 50, MLV_COLOR_GREY);
            MLV_draw_filled_rectangle(500+(j*50), i*50, 50, 50, MLV_rgba(50, 50, 50, 150));
            if (i<=3 && j<=3){
                 MLV_draw_filled_rectangle(500+(50*j), i*50, 50, 50, MLV_rgba(100, 0, 0, 150));
            }
            if (plateau.tab[i][j]==1 || plateau.tab[i][j]==3){
                MLV_draw_filled_rectangle(505+(j*50), (i*50)+5, 40, 40, MLV_COLOR_BLUE);
            }
        }
    }

    /* création de l'interface affichant le bloc suivant */
    
    MLV_draw_rectangle(1150, 250, 450, 400, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(1230, 280, "Next:", font_text_play, MLV_COLOR_WHITE);
    for (i=0; i<=3; i++){
        for (j=0; j<=3; j++){
            MLV_draw_rectangle(1225+(50*j), 380+(i*50), 50, 50, MLV_COLOR_GREY);
            MLV_draw_filled_rectangle(1225+(50*j), 380+(i*50), 50, 50, MLV_rgba(50, 50, 50, 150));
            MLV_draw_filled_rectangle(1225+(50*j), 380+(i*50), 50, 50, MLV_rgba(100, 0, 0, 150));
            if (piece_suivante.forme[i][j]==1){
                MLV_draw_filled_rectangle(1230+(j*50), (i*50)+385, 40, 40, MLV_COLOR_BLUE);
            }
        }
    }

    /* création d'un bloc d'affichage du score */

    sprintf(chaine_score, "%d", score_en_cours);
    MLV_draw_rectangle(100, 100, 300, 100, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(110, 110, chaine_score, font_score_play, MLV_COLOR_BLUE);

    /* affichage du temps de la partie */

    sprintf(chaine_temps, "%.0f s", temps_en_cours/1000);
    MLV_draw_rectangle(100, 300, 300, 100, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(110, 310, chaine_temps, font_score_play, MLV_COLOR_WHITE);

    /* actualise la fenêtre */
    
    MLV_actualise_window();
}

void generer_pause(MLV_Font* font_cross_pause, MLV_Font* font_arrow_pause, MLV_Font* font_text_pause){

    MLV_clear_window(MLV_COLOR_BLACK);

    /* création des boutons quitter et retour */
    
    MLV_draw_filled_rectangle(1450, 0, 50, 50, MLV_COLOR_RED);
    MLV_draw_filled_rectangle(0, 0, 50, 50, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(1460, 0, "X", font_cross_pause, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(8, 0, "--", font_arrow_pause, MLV_COLOR_BLUE);

    /* création d'un titre pour la fenêtre */

    MLV_draw_rectangle(500, 300, 500, 300, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(590, 310, "Game", font_text_pause, MLV_COLOR_RED);
    MLV_draw_text_with_font(570, 440, "Paused", font_text_pause, MLV_COLOR_RED);

    /* création de rectangles pour l'esthétique */

    MLV_draw_filled_rectangle(1000, 400, 500, 100, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(1000, 425, 500, 50, MLV_COLOR_BLUE);
    MLV_draw_filled_rectangle(0, 400, 500, 100, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(0, 425, 500, 50, MLV_COLOR_BLUE);

    /* actualise la fenêtre */
    
    MLV_actualise_window(); 
}

/* fonction générant le menu de sauvegarde */

void generer_save(MLV_Font* font_cross_save, MLV_Font* font_question_save, MLV_Font* font_text_save, MLV_Font* font_button_save){

    MLV_clear_window(MLV_COLOR_BLACK);

    /* création du bouton quitter */
    
    MLV_draw_filled_rectangle(1450, 0, 50, 50, MLV_COLOR_RED);
    MLV_draw_text_with_font(1460, 0, "X", font_cross_save, MLV_COLOR_WHITE);

    /* affichage du texte */
    
    MLV_draw_text_with_font(80, 250, "Would you like to save your game in progress?", font_question_save, MLV_COLOR_WHITE);

    /* création du bouton de sauvegarde */
    
    MLV_draw_filled_rectangle(200, 450, 500, 100, MLV_COLOR_GREEN);
    MLV_draw_rectangle(200, 450, 125, 100, MLV_COLOR_WHITE);
    MLV_draw_rectangle(325, 450, 125, 100, MLV_COLOR_WHITE);
    MLV_draw_rectangle(450, 450, 125, 100, MLV_COLOR_WHITE);
    MLV_draw_rectangle(575, 450, 125, 100, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(240, 470, "1.", font_button_save, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(365, 470, "2.", font_button_save, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(490, 470, "3.", font_button_save, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(615, 470, "4.", font_button_save, MLV_COLOR_WHITE);

    /* création du bouton retour (BOUTON NOPE) */
    
    MLV_draw_filled_rectangle(900, 450, 300, 100, MLV_COLOR_RED);
    MLV_draw_text_with_font(985, 480, "Nope", font_text_save, MLV_COLOR_WHITE);

    /* actualise la fenêtre */
    
    MLV_actualise_window();
}

/* fonction qui générant le menu de chargement */

void generer_load(MLV_Font* font_cross_load, MLV_Font* font_arrow_load, MLV_Font* font_text_load){

    MLV_clear_window(MLV_COLOR_BLACK);

    /* création des boutons quitter et retour */
    
    MLV_draw_filled_rectangle(1450, 0, 50, 50, MLV_COLOR_RED);
    MLV_draw_filled_rectangle(0, 0, 50, 50, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(1460, 0, "X", font_cross_load, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(8, 0, "--", font_arrow_load, MLV_COLOR_BLUE);

    /* création des boutons de chargement */
    
    MLV_draw_rectangle(600, 150, 300, 100, MLV_COLOR_WHITE);
    MLV_draw_rectangle(600, 350, 300, 100, MLV_COLOR_WHITE);
    MLV_draw_rectangle(600, 550, 300, 100, MLV_COLOR_WHITE);
    MLV_draw_rectangle(600, 750, 300, 100, MLV_COLOR_WHITE);

    /* affichage du texte dans les boutons */
    
    MLV_draw_text_with_font(675, 180, "Save 1", font_text_load, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(675, 380, "Save 2", font_text_load, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(675, 580, "Save 3", font_text_load, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(675, 780, "Save 4", font_text_load, MLV_COLOR_WHITE);

    /* création de lignes reliants les boutons (esthétique) */
    
    MLV_draw_filled_rectangle(680, 250, 140, 100, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(720, 250, 60, 100, MLV_COLOR_BLUE);
    MLV_draw_filled_rectangle(680, 450, 140, 100, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(720, 450, 60, 100, MLV_COLOR_BLUE);
    MLV_draw_filled_rectangle(680, 650, 140, 100, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(720, 650, 60, 100, MLV_COLOR_BLUE);

    /* actualise la fenêtre */
    
    MLV_actualise_window();
}

/* fonction générant le menu des scores */

int generer_scores(MLV_Font* font_cross_scores, MLV_Font* font_arrow_scores, MLV_Font* font_text_scores, MLV_Font* font_title_scores){

    /* création de variables et remise à vide de la fenêtre */
    
    int i;
    char chaine[TAILLE_CHAINE];
    FILE* fichier=NULL;
    MLV_clear_window(MLV_COLOR_BLACK);

    /* création des boutons quitter et retour */

    MLV_draw_filled_rectangle(1450, 0, 50, 50, MLV_COLOR_RED);
    MLV_draw_filled_rectangle(0, 0, 50, 50, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(1460, 0, "X", font_cross_scores, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(8, 0, "--", font_arrow_scores, MLV_COLOR_BLUE);

    /* affichage d'un texte score (titre du menu) */
    
    MLV_draw_text_with_font(480, 50, "Scores", font_title_scores, MLV_COLOR_RED);

    /* ouverture du fichier des scores en lecture */
    
    fichier=fopen("scores.txt", "r");
    i=0;
    if(fichier==NULL){
        printf("Vous tentez d'ouvrir un fichier inexsistant\n");
        return -1;
    }

    /* écriture des scores dans le leaderboard */
    
    while (fscanf(fichier, "%s", chaine)==1){
        MLV_draw_rectangle(600, 250+(70*i), 300, 70, MLV_COLOR_WHITE);
        MLV_draw_text_with_font(680, 265+(70*i), chaine, font_text_scores, MLV_COLOR_BLUE);
        i++;
    }

    /* actualise la fenêtre et ferme le fichier des scores */
    
    MLV_actualise_window();
    fclose(fichier);
    return 0;
}

/* fonction qui fait un petit affichage sympa et attend 3 secondes avant de retourner au menu principal */

void fin_de_partie(MLV_Font* font_text_fin){

    MLV_clear_window(MLV_COLOR_BLACK);

    /* création d'un affichage de Game Over */

    MLV_draw_rectangle(500, 300, 500, 300, MLV_COLOR_WHITE);
    MLV_draw_text_with_font(590, 310, "Game", font_text_fin, MLV_COLOR_RED);
    MLV_draw_text_with_font(590, 440, "Over", font_text_fin, MLV_COLOR_RED);

    /* création de rectangles d'esthétique */

    MLV_draw_filled_rectangle(625, 0, 250, 300, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(700, 0, 100, 300, MLV_COLOR_BLUE);
    MLV_draw_filled_rectangle(625, 600, 250, 400, MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(700, 600, 100, 400, MLV_COLOR_BLUE);

    /* actualise la fenêtre */
    
    MLV_actualise_window();

    /* attend 3 secondes */

    MLV_wait_seconds(3);
}

/* main ou fonction principale, autrement dit le coeur du programme */

int main(){

    /* déclaration des variables */
    
    int x, y; /* les coordonnées des clics de souris */
    int quitter=0; /* vérifie si l'utilisayeur veut quitter ou non. 0=NON et 1=OUI */
    int in_menu=1; /* vérifie que l'on soit dans le menu pricipal ou non. 0=NON et 1=OUI */
    int in_play=0; /* vérifie que l'on soit dans le jeu ou non. 0=NON et 1=OUI */
    int in_save=0; /* vérifie que l'on soit dans le menu de sauvegarde ou non. 0=NON et 1=OUI */
    int in_load=0; /* vérifie que l'on soit dans le menu de chargement ou non. 0=NON et 1=OUI */
    int in_scores=0; /* vérifie que l'on soit dans le menu des scores ou non. 0=NON et 1=OUI */
    int in_pause=0; /* vérifie que l'on soit dans le menu pause ou non. 0=NON et 1=OUI */
    int tab[N_SCORES]; /* tableau des scores */
    partie jeu_a_save; /* variable contenant toutes les données nécessaires à la sauvegarde d'une partie */
    grille plateau_en_cours; /* plateau principal de la partie en cours */
    piece piece_principale_en_cours; /* piece principale de la partie en cours */
    piece piece_suivante_en_cours; /* piece suivante de la partie en cours */
    int score_en_cours; /* score de la partie en cours */
    int vitesse_en_cours; /* la vitesse de descente d'une piece en nombre de frame */
    float temps_en_cours; /* le temps de la partie en cours */
    tab_parties t; /* tableau de toutes les parties sauvegardées */
    int vitesse_max_descente; /* variable qui permet de fixer la vitesse max pour la descente rapide de la pièce, pour ne pas qu'elle descende trop rapidement */
    int vitesse_max_deplacement; /* variable qui permet de fixer la vitesse max pour le déplacement à gauche et à droite de la pièce, pour ne pas qu'elle le fasse trop vite */
    int vitesse_max_rota; /* variable qui permet de fixer la vitesse max pour la rotation, pour pas que la piece ne tourne trop vite */
    int descente; /* variable qui vérifie si l'on doit descendre la pièce ou non en fonction de vitesse */
    int score_temp; /* score temporaire conetant le nombre de ligne suprrimée à chaque frame et que l'on ajoute au score total à chaque frame */
    piece piece_temp_rota; /* piece temporaire utilisée pour la rotation */
    int changer_temps; /* variable qui vérifie s'il faut réinitialiser le temps à 0 (corrige un bug bizzare) */
    
    /* variables de calcul du temps image par image */
    
    struct timespec debut;
    struct timespec fin;

    /* variables de vérification pour le jeu */

    int verif_fige_piece = -1; /* -1 si la pièce en cours n'est pas figée et 1 si la pièce se fige */
    int fin_partie; /* 20 si la partie continue (et on l'ajoutera au score quand il le faut, c'est le score lorsqu'une pièce se pose) et -1 si la partie est terminée */
    int vitesse_max; /* vitesse maximum de la descente d'une pièce */
    int nb_pose; /* calcule le nb de fois que la pièce a été posée */
 
    /* initialise la graine du temps pour faire de l'aléatoire */
    
    srand(time(NULL));

    /* initialisation des variables pour la partie en cours */


    descente=0;
    vitesse_en_cours=30;
    vitesse_max=6;
    nb_pose=0;
    vitesse_max_descente=2;
    vitesse_max_deplacement=5;
    vitesse_max_rota=5;
    plateau_en_cours=cree_plateau(20, 10);
    piece_principale_en_cours=generer_piece_aleatoire();
    piece_suivante_en_cours= generer_piece_aleatoire();
    score_en_cours=0;
    inserer_piece_grille(&plateau_en_cours, &piece_principale_en_cours);
    temps_en_cours=0;
    changer_temps=0;
    
    /* tests A SUPPRIMER
    
    plateau_en_cours.tab[0][0]=1;
    plateau_en_cours.tab[0][1]=1;
    afficher_plateau(&plateau_en_cours, 20, 10);
    printf("\n");
    afficher_piece(&piece_principale_en_cours);
    printf("\n");
    afficher_piece(&piece_suivante_en_cours);
    printf("\n");
    printf("%d\n", score_en_cours);
    printf("\n");
    score_en_cours=1000;
    en_cours_to_save(&jeu_a_save, plateau_en_cours, piece_principale_en_cours, piece_suivante_en_cours, score_en_cours);
    afficher_plateau(&(jeu_a_save.plateau), 20, 10);
    printf("\n");
    save_to_en_cours(jeu_a_save, &plateau_en_cours, &piece_principale_en_cours, &piece_suivante_en_cours, &score_en_cours);
    afficher_plateau(&plateau_en_cours, 20, 10);
    printf("\n");
    afficher_piece(&piece_principale_en_cours);
    printf("\n");
    afficher_piece(&piece_suivante_en_cours);
    printf("\n");
    printf("%d\n", score_en_cours);
    printf("\n");

    */

    /* génération de l'unique fenêtre du jeu */
    
    MLV_create_window( "Tetris", "Tetris", 1500, 1000);

    /* initialise l'interface son de MLV */

    MLV_init_audio();

    /* initialisation des fonts */

    MLV_Font* font_title_menu = MLV_load_font( "stocky.ttf", 200 );
    MLV_Font* font_text_menu = MLV_load_font ( "fast99.ttf", 50 );
    MLV_Font* font_cross_menu = MLV_load_font ( "fast99.ttf", 60 );
    MLV_Font* font_cross_play = MLV_load_font ( "fast99.ttf", 60 );
    MLV_Font* font_arrow_play = MLV_load_font ( "fast99.ttf", 60 );
    MLV_Font* font_text_play = MLV_load_font ( "fast99.ttf", 80 );
    MLV_Font* font_score_play = MLV_load_font ( "fast99.ttf", 90 );
    MLV_Font* font_cross_save = MLV_load_font ( "fast99.ttf", 60 );
    MLV_Font* font_question_save = MLV_load_font ( "SIXTY.TTF", 80);
    MLV_Font* font_text_save = MLV_load_font ( "fast99.ttf", 50 );
    MLV_Font* font_button_save = MLV_load_font ( "fast99.ttf", 70 );
    MLV_Font* font_cross_load = MLV_load_font ( "fast99.ttf", 60 );
    MLV_Font* font_arrow_load = MLV_load_font ( "fast99.ttf", 60 );
    MLV_Font* font_text_load = MLV_load_font ( "fast99.ttf", 50 );
    MLV_Font* font_cross_scores = MLV_load_font ( "fast99.ttf", 60 );
    MLV_Font* font_arrow_scores = MLV_load_font ( "fast99.ttf", 60 );
    MLV_Font* font_text_scores = MLV_load_font ( "fast99.ttf", 50 );
    MLV_Font* font_title_scores = MLV_load_font ( "stocky.ttf", 150 );
    MLV_Font* font_cross_pause = MLV_load_font ( "fast99.ttf", 60 );
    MLV_Font* font_arrow_pause = MLV_load_font ( "fast99.ttf", 60 );
    MLV_Font* font_text_pause = MLV_load_font ( "SIXTY.TTF", 150 );
    MLV_Font* font_text_fin = MLV_load_font ( "SIXTY.TTF", 150 );

    /* récupère l'audio à jouer en jeu */

    MLV_Music* music=MLV_load_music("lost_sky_dreams.ogg");

    /* première génération du menu principal */
    
    generer_menu(font_title_menu, font_text_menu, font_cross_menu);

/* boucle permettant la navigation entre les différents menus tant que l'on ne clique pas sur le bouton quiiter en haut à droite de la fenêtre */

    while(quitter==0){

        /* boucle qui gère les clics de souris et autres dans le menu principal */
        
        while(quitter==0 && in_menu==1){

            if(changer_temps==1){
                temps_en_cours=0;
                changer_temps=0;
            }

            /* attente d'un clic de l'utilisateur */
            
            MLV_wait_mouse(&x,&y);

            /* gère un clic potentiel du bouton quitter */
            
            if (x>=1450 && y<=50){
                quitter=1;
            }

            /* gère un clic potentiel du bouton play */
            
            if (600<=x && x<=900 && 400<=y && y<=500){
                generer_jeu(font_cross_play, font_arrow_play, font_text_play, font_score_play, plateau_en_cours, piece_suivante_en_cours, score_en_cours, temps_en_cours);
                in_menu=0;
                in_play=1;
                MLV_play_music(music, 1.0, -1);
            }

            /* gère un clic potentiel du bouton save */
            
            if (600<=x && x<=900 && 550<=y && y<=650){
                generer_save(font_cross_save, font_question_save, font_text_save, font_button_save);
                in_menu=0;
                in_save=1;
            }

            /* gère un clic potentiel du bouton load */

            if (600<=x && x<=900 && 700<=y && y<=800){
                generer_load(font_cross_load, font_arrow_load, font_text_load);
                in_menu=0;
                in_load=1;
            }

            /* gère un clic potentiel du bouton scores */
            
            if (600<=x && x<=900 && 850<=y && y<=950){
                generer_scores(font_cross_scores, font_arrow_scores, font_text_scores, font_title_scores);
                in_menu=0;
                in_scores=1;
            }
        }

        /* boucle du jeu  */
        
        while(quitter==0 && in_play==1){

            /* on récupère le temps de début */

            clock_gettime(CLOCK_REALTIME, &debut);

            /* on génère le jeu pour chaque frame */
            
            generer_jeu(font_cross_play, font_arrow_play, font_text_play, font_score_play, plateau_en_cours, piece_suivante_en_cours, score_en_cours, temps_en_cours);

            /* si un nombre de frame égal à la vitesse de descente se sont passées, alors on descend la pièce et on réinitialise descente à 0 */
            
            if (descente==vitesse_en_cours){
                verif_fige_piece=descendre_verticalement_piece(&plateau_en_cours, &piece_principale_en_cours, 20);
                descente=0;
                score_temp+=1;
            }

            /* si on apppuie sur s, la pièce descend plus vite, au rythme de 1 descente par frame */

            if (MLV_get_keyboard_state(MLV_KEYBOARD_s)==MLV_PRESSED && vitesse_max_descente==2){
                verif_fige_piece=descendre_verticalement_piece(&plateau_en_cours, &piece_principale_en_cours, 20);
                descente=0;
                vitesse_max_descente=0;
                score_temp+=1;
            }

            /* si on appuie sur d, la pièce se déplace vers la droite, seulement si c'est possible */

            if (MLV_get_keyboard_state(MLV_KEYBOARD_d)==MLV_PRESSED && vitesse_max_deplacement==5){
                deplacement_droite_gauche__piece(&plateau_en_cours, &piece_principale_en_cours, 10, 'd');
                vitesse_max_deplacement=0;
            }

            /* si on appuie sur q, la pièce se déplace vers la gauche, seulement si c'est possible */

            if (MLV_get_keyboard_state(MLV_KEYBOARD_q)==MLV_PRESSED && vitesse_max_deplacement==5){
                deplacement_droite_gauche__piece(&plateau_en_cours, &piece_principale_en_cours, 10, 'g');
                vitesse_max_deplacement=0;
            }

            /* si on appuie sur a, la pièce tourne vers la gauche de 90 degrés si c'est possible */

            if (MLV_get_keyboard_state(MLV_KEYBOARD_a)==MLV_PRESSED && vitesse_max_rota==5){
                deplacement_rotation(&plateau_en_cours, &piece_principale_en_cours, &piece_temp_rota, 20, 10, 'g');
                vitesse_max_rota=0;
            }

            /* si on appuie sur e, la pièce tourne vers la droite de 90 degrés si c'est possible */

            if (MLV_get_keyboard_state(MLV_KEYBOARD_e)==MLV_PRESSED && vitesse_max_rota==5){
                deplacement_rotation(&plateau_en_cours, &piece_principale_en_cours, &piece_temp_rota, 20, 10, 'd');
                vitesse_max_rota=0;
            }

            /* si la pièce s'est figé, on génère une nouvelle pièce et on gagne 20 points si on peut la générer, sinon, la partie se termine */
            
            if (verif_fige_piece==1){
                piece_principale_en_cours=piece_suivante_en_cours;
                piece_suivante_en_cours=generer_piece_aleatoire();
                fin_partie=inserer_piece_grille(&plateau_en_cours, &piece_principale_en_cours);
                verif_fige_piece=-1;
                nb_pose+=1;

                if (nb_pose==10 && vitesse_en_cours!=vitesse_max){
                    vitesse_en_cours-=3;
                    nb_pose=0;
                }

                /* si la partie se termine alors */
                
                if (fin_partie==-1){

                    /* on arrête la musique */

                    MLV_stop_music();

                    /* affichage d'une fenêtre de fin de partie */
                    
                    fin_de_partie(font_text_fin);

                    /* écriture du score dans le tableau des scores */
                    
                    ecrire_score(score_en_cours);

                    /* initialisation des variables pour la prochaine partie */
                    
                    descente=0;
                    vitesse_en_cours=30;
                    vitesse_max=6;
                    nb_pose=0;
                    vitesse_max_descente=2;
                    vitesse_max_deplacement=5;
                    vitesse_max_rota=5;
                    plateau_en_cours=cree_plateau(20, 10);
                    piece_principale_en_cours=generer_piece_aleatoire();
                    piece_suivante_en_cours= generer_piece_aleatoire();
                    score_en_cours=0;
                    inserer_piece_grille(&plateau_en_cours, &piece_principale_en_cours);
                    changer_temps=1;

                    /* retour au menu principal */
                    
                    generer_menu(font_title_menu, font_text_menu, font_cross_menu);
                    in_menu=1;
                    in_play=0;
                }

                /* sinon on ajoute +20 au score */
                
                else{
                    score_en_cours+=fin_partie;
                }
            }

            /* si une ligne est complète, on la supprime et on ajoute 50 au score_temp */

            score_temp+=verification_ligne(&plateau_en_cours, 20, 10);
            score_en_cours+=score_temp;
            score_temp=0;

            /* si on appuie sur echap, le menu de pause s'ouvre */

            if (MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE)==MLV_PRESSED){
                generer_pause(font_cross_pause, font_arrow_pause, font_text_pause);
                in_play=0;
                in_pause=1;

                /* on arrête la musique */

                MLV_stop_music();
            }

            /* on récupère le temps de fin */
            
            clock_gettime(CLOCK_REALTIME, &fin);

            /* on ajoute au temps total le temps de la frame */

            temps_en_cours+=(((fin.tv_sec*1000)+(fin.tv_nsec/1000000))-((debut.tv_sec*1000)+(debut.tv_nsec/1000000)));

            /* si on est en avance par rapport au frame rate voulu (30 FPS) on attend */
            
            if((1000/30)-(((fin.tv_sec*1000)+(fin.tv_nsec/1000000))-((debut.tv_sec*1000)+(debut.tv_nsec/1000000)))>0){
                MLV_wait_milliseconds((1000/30)-(((fin.tv_sec*1000)+(fin.tv_nsec/1000000))-((debut.tv_sec*1000)+(debut.tv_nsec/1000000))));
                temps_en_cours+=(1000/30)-(((fin.tv_sec*1000)+(fin.tv_nsec/1000000))-((debut.tv_sec*1000)+(debut.tv_nsec/1000000)));
            }

            /* frame terminée, on incrémente descente, et la vitesse_max_descente et vitesse_max_deplacement_et_rota si elle ne valent pas 2 et 10 */

            if (vitesse_max_descente!=2){
                vitesse_max_descente+=1;
            }

            if (vitesse_max_deplacement!=5){
                vitesse_max_deplacement+=1;
            }

            if (vitesse_max_rota!=5){
                vitesse_max_rota+=1;
            }
            
            descente+=1;
        }

        /* boucle qui gère les clics de souris et autres dans le menu de sauvegarde */
        
        while (quitter==0 && in_save==1){

            /* attente d'un clic de l'utilisateur */
            
            MLV_wait_mouse(&x,&y);

            /* gère un clic potentiel du bouton quitter */
            
            if (x>=1450 && y<=50){
                quitter=1;
            }

            /* gère un clic potentiel du bouton retour (BOUTON NOPE) */
            
            if (x<=1200 && 900<=x && y<=550 && 450<=y){
                generer_menu(font_title_menu, font_text_menu, font_cross_menu);
                in_menu=1;
                in_save=0;
            }

            /* gère un clic potentiel du bouton de sauvegarde N°1 */
            
            if (x<=325 && 200<=x && y<=550 && 450<=y){
                ecrire_save(plateau_en_cours, piece_principale_en_cours, piece_suivante_en_cours, score_en_cours, vitesse_en_cours, temps_en_cours, 0);
                generer_menu(font_title_menu, font_text_menu, font_cross_menu);
                in_menu=1;
                in_save=0;
            }

            /* gère un clic potentiel du bouton de sauvegarde N°2 */
            
            if (x<=450 && 325<=x && y<=550 && 450<=y){
                ecrire_save(plateau_en_cours, piece_principale_en_cours, piece_suivante_en_cours, score_en_cours, vitesse_en_cours, temps_en_cours, 1);
                generer_menu(font_title_menu, font_text_menu, font_cross_menu);
                in_menu=1;
                in_save=0;
            }

            /* gère un clic potentiel du bouton de sauvegarde N°3 */
            
            if (x<=575 && 450<=x && y<=550 && 450<=y){
                ecrire_save(plateau_en_cours, piece_principale_en_cours, piece_suivante_en_cours, score_en_cours, vitesse_en_cours, temps_en_cours, 2);
                generer_menu(font_title_menu, font_text_menu, font_cross_menu);
                in_menu=1;
                in_save=0;
            }

            /* gère un clic potentiel du bouton de sauvegarde N°4 */
            
            if (x<=700 && 575<=x && y<=550 && 450<=y){
                ecrire_save(plateau_en_cours, piece_principale_en_cours, piece_suivante_en_cours, score_en_cours, vitesse_en_cours, temps_en_cours, 3);
                generer_menu(font_title_menu, font_text_menu, font_cross_menu);
                in_menu=1;
                in_save=0;
            }
        }

        /* boucle qui gère les clics de souris et autres dans le menu de chargement */

        while (quitter==0 && in_load==1){

            /* attente d'un clic de l'utilisateur */
            
            MLV_wait_mouse(&x,&y);

            /* gère un clic potentiel du bouton quitter */
            
            if (x>=1450 && y<=50){
                quitter=1;
            }

            /* gère un clic potentiel du bouton retour */
            
            if (x<=50 && y<=50){
                generer_menu(font_title_menu, font_text_menu, font_cross_menu);
                in_menu=1;
                in_load=0;
            }

            /* gère un clic potentiel du bouton de chargement N°1 */
            
            if (x<=900 && 600<=x && y<=250 && 150<=y){
                load_partie(&plateau_en_cours, &piece_principale_en_cours, &piece_suivante_en_cours, &score_en_cours, &vitesse_en_cours, &temps_en_cours, 0);
                generer_menu(font_title_menu, font_text_menu, font_cross_menu);
                in_menu=1;
                in_load=0;
            }

            /* gère un clic potentiel du bouton de chargement N°2 */
            
            if (x<=900 && 600<=x && y<=450 && 350<=y){
                load_partie(&plateau_en_cours, &piece_principale_en_cours, &piece_suivante_en_cours, &score_en_cours, &vitesse_en_cours, &temps_en_cours, 1);
                generer_menu(font_title_menu, font_text_menu, font_cross_menu);
                in_menu=1;
                in_load=0;
            }

            /* gère un clic potentiel du bouton de chargement N°3 */
            
            if (x<=900 && 600<=x && y<=650 && 550<=y){
                load_partie(&plateau_en_cours, &piece_principale_en_cours, &piece_suivante_en_cours, &score_en_cours, &vitesse_en_cours, &temps_en_cours, 2);
                generer_menu(font_title_menu, font_text_menu, font_cross_menu);
                in_menu=1;
                in_load=0;
            }

            /* gère un clic potentiel du bouton de chargement N°4 */
            
            if (x<=900 && 600<=x && y<=850 && 750<=y){
                load_partie(&plateau_en_cours, &piece_principale_en_cours, &piece_suivante_en_cours, &score_en_cours, &vitesse_en_cours, &temps_en_cours, 3);
                generer_menu(font_title_menu, font_text_menu, font_cross_menu);
                in_menu=1;
                in_load=0;
            }
        }

        /* boucle qui gère les clics de souris et autres dans le menu des scores */
        
        while (quitter==0 && in_scores==1){

            /* attente d'un clic de l'utilisateur */
            
            MLV_wait_mouse(&x,&y);

            /* gère un clic potentiel du bouton quitter */
            
            if (x>=1450 && y<=50){
                quitter=1;
            }

            /* gère un clic potentiel du bouton retour */
            
            if (x<=50 && y<=50){
                generer_menu(font_title_menu, font_text_menu, font_cross_menu);
                in_menu=1;
                in_scores=0;
            }
        }

        /* boucle qui gère les clics de souris et autres dans le menu pause */

        while(in_pause==1 && quitter==0){
            
            MLV_wait_mouse(&x,&y);
            
            if (x>=1450 && y<=50){
                quitter=1;
            }
            
            if (x<=50 && y<=50){
                generer_menu(font_title_menu, font_text_menu, font_cross_menu);
                in_menu=1;
                in_pause=0;
            }
        }
    }

    /* ferme la fenêtre */
    
    MLV_free_window();

    /* tests A SUPPRIMER

    tmp_remplir_fichier_saves();
    remplir_tab_saves(t);
    tmp_afficher_plateau_saves(t);
    printf("%d\n", t[0].piece_principale.x);
    printf("%d\n", t[1].piece_principale.y);
    printf("%d\n", t[2].piece_suivante.forme[2][3]);
    printf("%d\n", t[3].score);

    afficher_plateau(&plateau_en_cours, 20, 10);
    printf("\n");
    afficher_piece(&piece_principale_en_cours);
    printf("\n");
    afficher_piece(&piece_suivante_en_cours);
    printf("\n");
    printf("%d\n", score_en_cours);
    printf("\n");

    */

    /* remplissage du fichier de sauvegarde avec des 0 A SUPPRIMER

    tmp_remplir_fichier_saves();

    */

    /* fin du programme */
    
    exit(EXIT_SUCCESS);
}
