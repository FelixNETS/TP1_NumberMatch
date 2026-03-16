// affichages.cpp			     
// Auteur: Jean-Christophe Latreille
// Date(derniere modif.) : 16 / 3 / 2026
// 
// Module qui g�re toutes les fonctions d'affichages du programme.
// IMPORTANT: ce module est le SEUL � utiliser la librairie "WinConsole" et des "printf()" !!
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "WinConsole.h"     //NOTE: ne doit PAS �tre inclus nullepart ailleurs dans le projet!
#include "affichages.h"

#define CH_MAX  9           //le chiffre maximal � afficher

/*****************************************************************************/






/******************* LES FONCTIONS SUIVANTES SONT DONN�ES ********************/
/*****************************************************************************/
//Affiche le message de demande d'une saisie de case ou commande (sur la ligne 3).
void demander_saisie(int no_saisie) {
    gotoxy(COL_GRILLE, LIG_SAISIE);             //saisie sur la ligne 2 de l'�cran
    printf("Entrer la case %d (eg. A1): ", no_saisie);
    clreol();           //effacer reste de cette ligne
}

/*****************************************************************************/
//Les 3 fonctions suivantes servent � afficher diff�rents messages durant le jeu :
void message(const char* mess) {
    /* affiche un message d'information � la ligne 3 pendant 3 secondes */
    textcolor(WHITE);   //remise � la couleur BLANC
    gotoxy(COL_GRILLE, LIG_MESSAGES);
    printf("%s", mess);   
    clreol();           //effacer le reste de l'ancien message affich� sur cette ligne
    delay(2000);        //= 3 secondes
}

/*****************************************************************************/
void mess_erreur(const char* mess) {
    /* affiche un message d'erreur � la ligne 3 en ROUGE avec clignotements! */
    for (int i = 0; i < 5; i++) {   //faire clignoter 5 fois
        gotoxy(COL_GRILLE, LIG_MESSAGES);
        textcolor(LIGHTRED);
        printf("%s", mess);         //afficher
        delay(500);
        gotoxy(COL_GRILLE, LIG_MESSAGES);
        clreol();                   //effacer
        delay(200);
    }
    textcolor(WHITE);  //remise � la couleur BLANC
}

/*****************************************************************************/
void mess_points(int pts) {
    /* affiche les points obtenus � la ligne 1 en VERT avec clignotements! */
    for (int i = 0; i < 3; i++) {    //faire clignoter 3 fois
        gotoxy(COL_GRILLE + 20, LIG_POINTS);
        textcolor(LIGHTGREEN);
        printf("+%d points!!", pts); //afficher
        delay(300);
        gotoxy(COL_GRILLE + 20, LIG_POINTS);
        clreol();                    //effacer
        delay(100);
    }
    textcolor(WHITE);  //remise � la couleur BLANC
}

/*********************** IMPLEMENTATION DES FONCTIONS ************************/
/*****************************************************************************/
void afficher_infos_jeu(const t_tab_chiffres nbr_chiffres, int pts) {
    int i;  // Compteur pour passer tous les chiffres possibles
    
    char str_score[] = "Score: ";   // Texte pour la ligne de score
    char str_chiffres[] = "Chiffres: "; // Texte pour la ligne des chiffres restants

    int centre = WIDTH_CONSOLE / 2, // Centre de la console

        // Calcul pour centrer la ligne du score. On retire a la valeur du centre
        //la moitie de: la longueur du string + nb de cases pour le pointage.
        x_score = centre - ((strlen(str_score) + NB_POSI_SCORE) / 2);

    gotoxy(x_score, LIG_POINTS);    // On va a la position calculee pour centrer le score
    printf("%s%3d", str_score, pts);    // On affiche le texte de score ainsi que les points

    // On va a la position calculee pour centrer les chiffres
    gotoxy(COL_GRILLE, LIG_CHIFFRES);
    printf("%s", str_chiffres); // On affiche le texte de la ligne de chiffres restants

    // Boucle for qui passe chaque chiffre possible
    for (i = 1; i <= CH_MAX; i++) {
        if (nbr_chiffres[i] > 0) {  // Si le chiffre est encore disponible dans la grille
            printf("%d ", i);   // On affiche le chiffre disponible
        }
        else {  // Si le chiffre n'est pas disponible dans la grille
            printf("  ");   // On affiche un espace vide
        }
    }
}

/*****************************************************************************/
void afficher_grille(const t_grille_nos grille, int dern_lig) {
    int lig, col;
    char indices_col[] = "ABCDEFGHI";   // Labels des colonnes A a I (colonnes 1 a 9)

    // Afficher les en-tetes de colonnes sur la ligne au-dessus de la grille
    gotoxy(COL_GRILLE, LIG_GRILLE - 1);
    printf("   ");  // Espace pour le numero de ligne
    textcolor(YELLOW);
    for (col = 1; col < NB_COL; col++) {
        printf("%c ", indices_col[col - 1]);
    }
    textcolor(WHITE);   // Remise a la couleur BLANC

    // Afficher chaque ligne de la grille
    for (lig = 0; lig <= dern_lig; lig++) {
        gotoxy(COL_GRILLE, LIG_GRILLE + lig);
        printf("%2d ", lig + 1);    // Numero de ligne (1-base)
        for (col = 1; col < NB_COL; col++) {
            if (grille[lig][col] != 0) {
                printf("%d ", grille[lig][col]);    // Afficher le chiffre
            } else {
                printf("  ");   // Case vide
            }
        }
        clreol();   // Effacer le reste de la ligne
    }
}
