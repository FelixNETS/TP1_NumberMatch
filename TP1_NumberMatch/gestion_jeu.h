// gestion_jeu.h
// Auteur: F�lix Nadeau
// Date (derni�re modif.): 16/3/2026
// 
// FICHIER HEADER 
// utilis� pour le module de gestion du jeu gestion_jeu.cpp

/******************** LIBRAIRIES INCLUSES **********************/

#include <string.h>
#include <math.h>
#include <ctype.h>
#include "affichages.h"

/********************** LES CONSTANTES *************************/

#define CODE_CHIFFRES -2		//demander une r�g�n�ration de nouveaux chiffres 
#define CODE_AIDE -1			//demander une suggestion d�un coup � jouer 
#define CODE_QUITTER 0			//code pour quitter le jeu 

#define PTS_COUPLE_VOISIN  1	//�limination d'un couple de chiffres voisins (distance de 1) 
#define PTS_COUPLE_SEPARE  4	//�limination d'un couple de chiffres s�par�s par des espaces 
#define PTS_LIGNE_RETIREE  10	//�limination d'une ligne vide suite � un retrait de chiffres 

#define COUP_MAXLONG 3			//quantit� maximale de char permis pour l'entr�e de coup

/****************** D�CLARATIONS DES MACROS ********************/

#define CHIFFRES_A_VAL(ch) ((ch) - '0')		//conversion CHAR nombre -> valeur �quivalente
#define LETTRE_A_COL(let) (let - 'A' + 1)	//conversion CHAR lettre -> colonne �quivalente
#define COL_A_LETTRE(col) (col + 'A' - 1)	//conversion INT colonne -> lettre �quivalente

/******************** FONCTIONS PUBLIQUES **********************/

// validation & analyse de la commande saisie par le joueur 
// fonction priv�e au module gestion_jeu.cpp
// PARAMS: la derni�re ligne de la grille et le # de la saisie actuelle
// RETOUR: soit un des code sp�ciaux ou la position saisie
int valider_coup(t_liste_couples liste, int derniere_lig, int* caseA, int* caseB);

// validation & analyse de la commande saisie par le joueur 
// fonction priv�e au module gestion_jeu.cpp
// PARAMS: la derni�re ligne de la grille et le # de la saisie actuelle
// RETOUR: soit un des code sp�ciaux ou la position saisie
int jouer_coup(t_grille_nos grille, t_tab_chiffres nbr_chiffres,
	int* derniere_lig, int caseA, int caseB);

// Affiche le coup sugg�r� en format texte et met en �vidence les deux cases en BLEU.
// PARAM.: la grille de jeu, des r�f�rences aux deux cases du coup sugg�r� (caseA, caseB)
// RETOUR: aucun
void afficher_indice(t_grille_nos grille, int* caseA, int* caseB);

/***************************************************************/