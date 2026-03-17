// gestion_jeu.h
// Auteur: Félix Nadeau
// Date (dernière modif.): 13/3/2026
// 
// FICHIER HEADER 
// utilisé pour le module de gestion du jeu gestion_jeu.cpp

/******************** LIBRAIRIES INCLUSES **********************/

#include <string.h>
#include <math.h>
#include <ctype.h>
#include "affichages.h"

/********************** LES CONSTANTES *************************/

#define CODE_CHIFFRES -2		//demander une régénération de nouveaux chiffres 
#define CODE_AIDE -1			//demander une suggestion d’un coup à jouer 
#define CODE_QUITTER 0			//code pour quitter le jeu 

#define PTS_COUPLE_VOISIN  1	//élimination d'un couple de chiffres voisins (distance de 1) 
#define PTS_COUPLE_SEPARE  4	//élimination d'un couple de chiffres séparés par des espaces 
#define PTS_LIGNE_RETIREE  10	//élimination d'une ligne vide suite à un retrait de chiffres 

#define COUP_MAXLONG 3			//quantité maximale de char permis pour l'entrée de coup

/****************** DÉCLARATIONS DES MACROS ********************/

#define CHIFFRES_A_VAL(ch) ((ch) - '0')		//conversion CHAR nombre -> valeur équivalente
#define LETTRE_A_COL(let) (let - 'A' + 1)	//conversion CHAR lettre -> colonne équivalente
#define COL_A_LETTRE(col) (col + 'A' - 1)	//conversion INT colonne -> lettre équivalente

/******************** FONCTIONS PUBLIQUES **********************/

// validation & analyse de la commande saisie par le joueur 
// fonction privée au module gestion_jeu.cpp
// PARAMS: la dernière ligne de la grille et le # de la saisie actuelle
// RETOUR: soit un des code spéciaux ou la position saisie
int valider_coup(t_liste_couples liste, int derniere_lig, int* caseA, int* caseB);

// validation & analyse de la commande saisie par le joueur 
// fonction privée au module gestion_jeu.cpp
// PARAMS: la dernière ligne de la grille et le # de la saisie actuelle
// RETOUR: soit un des code spéciaux ou la position saisie
int jouer_coup(t_grille_nos grille, t_tab_chiffres nbr_chiffres,
	int* derniere_lig, int caseA, int caseB);

void afficher_indice(t_grille_nos grille, int* caseA, int* caseB);

/***************************************************************/