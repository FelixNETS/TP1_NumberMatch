// liste_couples.h			(*** FICHIER DONNÉ ***)
// Auteur: Eric Thé, déc. 2025
// 
// Module qui gère la liste des coups possibles à jouer.
// Les coups sont représentés par deux entiers qui représentent 2 cases de la grille de jeu.
// Format : chiffre des unités = no. de colonne (1 à 9), 2ième et 3ième chiffres = no. ligne.
//          Ex. 24 - 34 == case [2][4] et case [3][4] == "D3" - "D4" (pour le joueur)
// 
// La ligne [LIG_INFOS] (ligne 0) contient la taille totale dans la colonne [COL_TAILLE] (= 0)
// ainsi que le nb. d'éléments actuels dans la colonne [COL_NB_ELEM] (= 1).
#ifndef MAX_COUPLES
#include "utilitaires.h"	//pour les fonctions aléatoires

/********************** LES CONSTANTES *************************/
#define MAX_COUPLES 200		//taille maximale de la liste
#define LIG_INFOS   0		//position-ligne pour les infos de la liste
#define COL_TAILLE  0		//position-colonne de la taille totale (à la ligne [0])
#define COL_NBELEM  1		//position-colonne du nb. d'éléments (à la ligne [0])

/******************* DÉCLARATION DES TYPES *********************/
//Type-tableau pour la liste. Contient 2 colonnes pour les deux cases à jouer.
typedef int t_liste_couples[MAX_COUPLES + 1][2];   //eg. 24 - 34 (== "D3" - "D4")

/***************** DÉCLARATIONS DES FONCTIONS ******************/

//remise à zéro de la liste des couples (les coups possibles)
//PARAM.: la liste des coups possibles
void init_liste_couples(t_liste_couples liste);

//accesseur au nb. d'éléments dans la liste
//PARAM.: la liste des coups possibles
//RETOUR: (entier) le nb. d'élémengts actuels
int  nb_couples(const t_liste_couples liste);

//permet d'ajouter un nouveau couple à la liste des coups possibles.
//PARAM.: la liste des coups possibles et les deux cases à jouer
//RETOUR: (entier) 1 si le couple a pu être ajouté, 0 sinon (liste pleine)
int  ajouter_couple(t_liste_couples liste, int caseA, int caseB);

//vérifie si la liste des coups contient déjà [caseA, caseB] (OU [caseB, caseA]).
//PARAM.: la liste des coups possibles et les deux cases à jouer
//RETOUR: 1 si ce couple est présent dans la liste, 0 sinon.
int  liste_contient(t_liste_couples liste, int caseA, int caseB);

//permet de choisir un des coups possibles aléatoirement (pour la commande "??")
//PARAM.: la liste des coups possibles et deux références aux 2 cases à jouer
//RETOUR: aucun, mais le couple choisi aléatoirement est retourné via les références
void choix_couple_alea(const t_liste_couples liste, int *caseA, int *caseB);

#endif