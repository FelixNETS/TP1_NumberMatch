// affichages.cpp			     
// Auteur: Jean-Christophe Latreille et Felix Nadeau
// Date(derniere modif.) : 16 / 3 / 2026
// 
// Module qui g�re toutes les fonctions d'affichages du programme.
// IMPORTANT: ce module est le SEUL � utiliser la librairie "WinConsole" et des "printf()" !!
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WinConsole.h"     //NOTE: ne doit PAS �tre inclus nullepart ailleurs dans le projet!
#include "affichages.h"

#define CH_MAX  9           //le chiffre maximal � afficher

/*****************************************************************************/



/*****************************************************************************/
void afficher_instructions() {

    char texte[11][100];    // tableau de strings, phrases d'instruction

    // declaration des phrases d'instruction
    strcpy(texte[0], "***NUMBER MATCH***\n");
    strcpy(texte[1], "Le but du jeu est d'eliminer des couples de chiffres\n");
    strcpy(texte[2], "Les couples possibles sont deux chiffres identiques (7 et 7)");
    strcpy(texte[3], "ou deux chiffres dont la somme est 10 (7 et 3)\n");
    strcpy(texte[4], "les couples doivent se voir dans une des huit direction cardinales");
    strcpy(texte[5], "et ne pas avoir d'autres chiffres entre eux pour etre valides\n");
    strcpy(texte[6], "Si on elimine un ligne complete, elle disparait\n");
    strcpy(texte[7], "ASSIGN. POINTAGE:                 CODES SPECIAUX:     ");
    strcpy(texte[8], "Elim. couple colle:  1  pt        ++: Ajout. Chiffres ");
    strcpy(texte[9], "Elim. couple separe: 4  pts       ??: Indince         ");
    strcpy(texte[10], "Vide ligne:          10 pts       XX: Quitter        ");

    // boucle FOR pour imprimer le texte bien centré
    // print un buffer (texte vide) de longueur (width - longueur du texte) / 2)
    // cela place le curseur a la bonne pos. pour print la phrase centrée
    // ensuite on imprime chaque phrase du tableau
    for (int i = 0; i < 11; i++) {
        printf("%*s%s\n", (WIDTH_CONSOLE - strlen(texte[i])) / 2, "", texte[i]);
    }

    // ATTENTE DU DEPART
    gotoxy(10, 22);
    system("pause");
}

/******************* LES FONCTIONS SUIVANTES SONT DONN�ES ********************/
/*****************************************************************************/
//Affiche le message de demande d'une saisie de case ou commande (sur la ligne 3).
void demander_saisie(int no_saisie) {
    gotoxy(COL_MESSAGE, LIG_SAISIE);             //saisie sur la ligne 2 de l'�cran
    printf("Entrer la case %d (eg. A1): ", no_saisie);
    clreol();           //effacer reste de cette ligne
}

/*****************************************************************************/
//Les 3 fonctions suivantes servent � afficher diff�rents messages durant le jeu :
void message(const char* mess) {
    /* affiche un message d'information � la ligne 3 pendant 3 secondes */
    textcolor(WHITE);   //remise � la couleur BLANC
    gotoxy(COL_MESSAGE, LIG_MESSAGES);
    printf("%s", mess);
    clreol();           //effacer le reste de l'ancien message affich� sur cette ligne
    delay(2000);        //= 3 secondes
}

/*****************************************************************************/
void mess_erreur(const char* mess) {
    /* affiche un message d'erreur � la ligne 3 en ROUGE avec clignotements! */
    for (int i = 0; i < 5; i++) {   //faire clignoter 5 fois
        gotoxy(COL_MESSAGE, LIG_MESSAGES);
        textcolor(LIGHTRED);
        printf("%s", mess);         //afficher
        delay(500);
        gotoxy(COL_MESSAGE, LIG_MESSAGES);
        clreol();                   //effacer
        delay(200);
    }
    textcolor(WHITE);  //remise � la couleur BLANC
}

/*****************************************************************************/
void mess_points(int pts) {
    /* affiche les points obtenus � la ligne 1 en VERT avec clignotements! */
    for (int i = 0; i < 3; i++) {    //faire clignoter 3 fois
        gotoxy(COL_MESSAGE + 20, LIG_POINTS);
        textcolor(LIGHTGREEN);
        printf("+%d points!!", pts); //afficher
        delay(300);
        gotoxy(COL_MESSAGE + 20, LIG_POINTS);
        clreol();                    //effacer
        delay(100);
    }
    textcolor(WHITE);  //remise � la couleur BLANC
}

/*********************** IMPLEMENTATION DES FONCTIONS ************************/

/*---------------------- afficher_infos_jeu() ---------------------------*/
void afficher_infos_jeu(const t_tab_chiffres nbr_chiffres, int pts) {
    int i;  // Compteur pour passer tous les chiffres possibles

    char str_score[] = "Score: ";   // Texte pour la ligne de score
    char str_chiffres[] = "Chiffres: "; // Texte pour la ligne des chiffres restants

    int centre = WIDTH_CONSOLE / 2, // Centre de la console

        // Calcul pour centrer la ligne du score. On retire a la valeur du centre
        //la moitie de: la longueur du string + nb de cases pour le pointage.
        x_score = centre - ((strlen(str_score) + NB_POSI_SCORE) / 2);

    clrscr();

    gotoxy(x_score, LIG_POINTS);    // On va a la position calculee pour centrer le score
    printf("%s%3d", str_score, pts);    // On affiche le texte de score ainsi que les points

    // On va a la position calculee pour centrer les chiffres
    gotoxy(COL_MESSAGE, LIG_CHIFFRES);
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


/*------------------------- afficher_grille() ---------------------------*/
void afficher_grille(const t_grille_nos grille, int dern_lig) {
    int lig, col;
    char indices_col[] = "ABCDEFGHI";   // Labels des colonnes A a I (colonnes 1 a 9)

    // Afficher les en-tetes de colonnes sur la ligne au-dessus de la grille
    gotoxy(COL_LETTRES, LIG_GRILLE - 1);
    textcolor(YELLOW);
    for (col = 1; col < NB_COL; col++) {
        printf("%c ", indices_col[col - 1]);
    }
    textcolor(WHITE);   // Remise a la couleur BLANC

    // Afficher chaque ligne de la grille
    for (lig = 0; lig < dern_lig; lig++) {

        //Afficher les numéros de ligne
        gotoxy(COL_CHIFFRES, LIG_GRILLE + lig);
        textcolor(YELLOW);
        printf("%2d", lig + 1);    // Numero de ligne (1-base)
        textcolor(WHITE);

        //Afficher les chiffres de la grille
        for (col = 1; col < NB_COL; col++) {
            gotoxy(COL_GRILLE + (col * 2), LIG_GRILLE + lig);
            if (grille[lig][col])printf("%d", grille[lig][col]);
            else printf(" ");
        }
    }
}


/*------------------------- afficher_couple() ---------------------------*/
void afficher_couple(int colA, int ligA, int chA, int colB, int ligB, int chB) {
    gotoxy((2 * colA) + COL_GRILLE, ligA + LIG_GRILLE);     // On se positionne sur la case A
    textcolor(BLUE);        // On change la couleur du texte a bleu
    printf("%d", chA);      // On re-ecrit la valeur de la case A en bleu

    gotoxy((2 * colB) + COL_GRILLE, ligB + LIG_GRILLE);     // On se positionne sur la case B
    printf("%d", chB);      // On re-ecrit la valeur de la case B en bleu

    delay(ATT_INDICE);      // On attend

    gotoxy((2 * colA) + COL_GRILLE, ligA + LIG_GRILLE);     // On se positionne sur la case A
    textcolor(WHITE);       // On change la couleur du texte a blanc
    printf("%d", chA);      // On re-ecrit la valeur de la case A en blanc

    gotoxy((2 * colB) + COL_GRILLE, ligB + LIG_GRILLE);     // On se positionne sur la case B
    printf("%d", chB);      // On re-ecrit la valeur de la case B en blanc
}