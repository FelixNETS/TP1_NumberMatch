// grille_chiffres.h		(*** FICHIER DONN� ***)
// Auteur: Eric Th�, d�c. 2025
// 
// Module qui g�re la grille des chiffres ainsi que la liste des chiffres encore disponibles.
// Format de la grille: 
//  - la colonne [POS_NB] (= [0]) de chaque ligne contient le nb. de chiffres sur cette ligne
// 
// Format de la liste des chiffres dispos.:
//  - la case [POS_NB] (= [0]) du tableau contient le nb. de chiffres restants (= 9 au d�part)
//  - les autres cases indiquent le nb. de fois que chaque chiffre est pr�sent dans la grille
//    eg. si la case [1] contient 4, cela indique qu'il y a 4 fois le chiffre '1' dans le jeu 
//
// Offre des fonctions qui permettent de:
//  - initialiser la grille
//  - ajouter de nouveaux chiffres alea. lorsque n�cessaire ou demand�
//  - g�n�rer la liste des couples possibles � jouer
//  - retirer un chiffre dans la grille
//  - retirer un chiffre de la liste des chiffres dispos
//  - obtenir le chiffre se trouvant dans une case donn�e de la grille

#ifndef OK_GRILLE
#define OK_GRILLE  

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "liste_couples.h"    //va aussi inclure le module "utilitaires.h"

/********************** LES CONSTANTES *************************/

//Les deux dimensions de la grille de jeu
#define NB_COL  10		 //10 = la colonne du nb. chiffres + 9 chiffres (colonnes [1] � [9])
#define MAX_LIG 20		 //20 lignes de chiffres max. (� partir de [0])

#define MIN_NB_NOUV 1.5	 //facteur du nb. minimum de chiffres � reg�n�rer (commande "++")
#define MAX_NB_NOUV 5.0	 //facteur du nb. maximum de chiffres � reg�n�rer

#define POS_NB  0		 //position du compteur du nb. d'�l�ments dans un t_tab_chiffres
						 //ET dans la grille des chiffres (la colonne [0] de chaque ligne)

#define CASE_VIDE 0		 //valeur repr�sentant une case vide dans la grille


/******************* D�CLARATION DES TYPES *********************/

//Type-tableau pour la grille de jeu (tableau 2D)
typedef int t_grille_nos[MAX_LIG][NB_COL];

//Type-tableau de la liste des chiffres dispos. (tableau 1D)
typedef int t_tab_chiffres[NB_COL];


/***************** D�CLARATIONS DES FONCTIONS ******************/

//Re�oit une grille vide et g�n�re les premieres lignes de chiffres alea.
//Le nombre de chiffres g�n�r�s pour chaque chiffre sera retenu dans "nbr_chiffres[]"
//PARAM.: la grille de jeu � remplir et la listes des chiffres dispos
//RETOUR: l'indice de la derni�re ligne avec au moins un chiffre apr�s l'initialisation
int init_grille(t_grille_nos grille, t_tab_chiffres nbr_chiffres);

//Permet de g�n�rer la liste de tous les coups (couples) possibles � jouer.
//PARAM.: la grille de jeu, sa derni�re ligne et la listes des coups possibles � remplir
//RETOUR: Le nombre de couples possibles r�pertori�s pour le prochain coup � jouer
int generer_listes_couples(const t_grille_nos grille, int dern_lig, t_liste_couples liste);

//Permet de retirer la ligne vide [no_lig] de la grille des chiffres.
//Les lignes suivantes seront toutes recopi�e UNE ligne plus haut pour remplir l'espace vide.
//PARAM.: la grille de jeu et l'indice de la ligne vide � supprimer
//RETOUR: aucun
void retirer_ligne(t_grille_nos grille, int no_lig);

//Permet d'effacer (mettre � z�ro) la case "pos" de la grille de jeu.
//Le nb. de chiffres de cette ligne sera aussi d�cr�ment� (dans la colonne [0] de cette ligne)
//PARAM.: la grille de jeu et la position de la case � vider (eg. 24 == case [2][4])
//RETOUR: aucun
void effacer_chiffre(t_grille_nos grille, int pos);

//Permet de retirer (mettre � z�ro) le chiffre "ch" de la liste des chiffres dispos.
//Ap�s ce retrait ce chiffre ne sera plus g�n�r� lors des prochaines reg�n�rations de chiffres
//Le nb. de chiffres dispos du tableau sera aussi d�cr�ment� (compteur dans la case [0])
//PARAM.: le chiffre � retirer et la listes des chiffres dispos
//RETOUR: retour du m�me chiffre "ch" si ce chiffre n'est plus pr�sent dans le jeu, 0 sinon.
int  retirer_chiffre(int ch, t_tab_chiffres nbr_chiffres);

//Accesseur au chiffre se trouvant � la case "no_case" de la grille.
//PARAM.: la grille de jeu et la position de la case d�sir�e (eg. 24 == case [2][4])
//RETOUR: (entier) le chiffre qui se trouve � cette position de la grille
int  get_chiffre_case(const t_grille_nos grille, int no_case);

//Accesseur au nb. de chiffres restants dans le jeu (la case [0] du tableau).
//Note: le jeu se termine lorsque cette fonction retourne 0 (plus de chiffres).
//PARAM.: la listes des chiffres dispos
//RETOUR: (entier) le nb. de chiffres encore disponibles
int  nb_chiffres_restants(const t_tab_chiffres nbr_chiffres);

//Permet de g�n�rer de nouveau chiffres alea. qui seront ajout�s � la suite des
//chiffre restants dans la grille de jeu.
//Le nombre de chiffres g�n�r�s pour chaque chiffre sera ajout� � "nbr_chiffres[]".
//PARAM.: la grille de jeu, la listes des chiffres dispos et une r�f�rence � la derni�re ligne
//RETOUR: aucun, mais l'indice de la derni�re ligne avec au moins un chiffre sera modifi�
void ajouter_chiffres(t_grille_nos grille, t_tab_chiffres nbr_chiffres, int* dern_lig);

#endif