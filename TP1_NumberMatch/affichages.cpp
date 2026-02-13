// affichages.cpp			     
// Auteur: 
// Date:
// 
// Module qui gère toutes les fonctions d'affichages du programme.
// IMPORTANT: ce module est le SEUL à utiliser la librairie "WinConsole" et des "printf()" !!
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "WinConsole.h"     //NOTE: ne doit PAS être inclus nullepart ailleurs dans le projet!
#include "affichages.h"

#define CH_MAX  9           //le chiffre maximal à afficher

/*****************************************************************************/






/******************* LES FONCTIONS SUIVANTES SONT DONNÉES ********************/
/*****************************************************************************/
//Affiche le message de demande d'une saisie de case ou commande (sur la ligne 3).
void demander_saisie(int no_saisie) {
    gotoxy(COL_GRILLE, LIG_SAISIE);             //saisie sur la ligne 2 de l'écran
    printf("Entrer la case %d (eg. A1): ", no_saisie);
    clreol();           //effacer reste de cette ligne
}

/*****************************************************************************/
//Les 3 fonctions suivantes servent à afficher différents messages durant le jeu :
void message(const char* mess) {
    /* affiche un message d'information à la ligne 3 pendant 3 secondes */
    textcolor(WHITE);   //remise à la couleur BLANC
    gotoxy(COL_GRILLE, LIG_MESSAGES);
    printf("%s", mess);   
    clreol();           //effacer le reste de l'ancien message affiché sur cette ligne
    delay(2000);        //= 3 secondes
}

/*****************************************************************************/
void mess_erreur(const char* mess) {
    /* affiche un message d'erreur à la ligne 3 en ROUGE avec clignotements! */
    for (int i = 0; i < 5; i++) {   //faire clignoter 5 fois
        gotoxy(COL_GRILLE, LIG_MESSAGES);
        textcolor(LIGHTRED);
        printf("%s", mess);         //afficher
        delay(500);
        gotoxy(COL_GRILLE, LIG_MESSAGES);
        clreol();                   //effacer
        delay(200);
    }
    textcolor(WHITE);  //remise à la couleur BLANC
}

/*****************************************************************************/
void mess_points(int pts) {
    /* affiche les points obtenus à la ligne 1 en VERT avec clignotements! */
    for (int i = 0; i < 3; i++) {    //faire clignoter 3 fois
        gotoxy(COL_GRILLE + 20, LIG_POINTS);
        textcolor(LIGHTGREEN);
        printf("+%d points!!", pts); //afficher
        delay(300);
        gotoxy(COL_GRILLE + 20, LIG_POINTS);
        clreol();                    //effacer
        delay(100);
    }
    textcolor(WHITE);  //remise à la couleur BLANC
}