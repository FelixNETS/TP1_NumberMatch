// grille_chiffres.h		(*** FICHIER DONNÉ ***)
// Auteur: Eric Thé, déc. 2025
// 
// Module qui gère la grille des chiffres ainsi que la liste des chiffres encore disponibles.
// Format de la grille: 
//  - la colonne [POS_NB] (= [0]) de chaque ligne contient le nb. de chiffres sur cette ligne
// 
// Format de la liste des chiffres dispos.:
//  - la case [POS_NB] (= [0]) du tableau contient le nb. de chiffres restants (= 9 au départ)
//  - les autres cases indiquent le nb. de fois que chaque chiffre est présent dans la grille
//    eg. si la case [1] contient 4, cela indique qu'il y a 4 fois le chiffre '1' dans le jeu 
//
// Offre des fonctions qui permettent de:
//  - initialiser la grille
//  - ajouter de nouveaux chiffres alea. lorsque nécessaire ou demandé
//  - générer la liste des couples possibles à jouer
//  - retirer un chiffre dans la grille
//  - retirer un chiffre de la liste des chiffres dispos
//  - obtenir le chiffre se trouvant dans une case donnée de la grille

#ifndef OK_GRILLE
#define OK_GRILLE  

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "liste_couples.h"    //va aussi inclure le module "utilitaires.h"

/********************** LES CONSTANTES *************************/

//Les deux dimensions de la grille de jeu
#define NB_COL  10		 //10 = la colonne du nb. chiffres + 9 chiffres (colonnes [1] à [9])
#define MAX_LIG 20		 //20 lignes de chiffres max. (à partir de [0])

#define MIN_NB_NOUV 1.5	 //facteur du nb. minimum de chiffres à regénérer (commande "++")
#define MAX_NB_NOUV 5.0	 //facteur du nb. maximum de chiffres à regénérer

#define POS_NB  0		 //position du compteur du nb. d'éléments dans un t_tab_chiffres
						 //ET dans la grille des chiffres (la colonne [0] de chaque ligne)


/******************* DÉCLARATION DES TYPES *********************/

//Type-tableau pour la grille de jeu (tableau 2D)
typedef int t_grille_nos[MAX_LIG][NB_COL];

//Type-tableau de la liste des chiffres dispos. (tableau 1D)
typedef int t_tab_chiffres[NB_COL];


/***************** DÉCLARATIONS DES FONCTIONS ******************/

//Reçoit une grille vide et génére les premieres lignes de chiffres alea.
//Le nombre de chiffres générés pour chaque chiffre sera retenu dans "nbr_chiffres[]"
//PARAM.: la grille de jeu à remplir et la listes des chiffres dispos
//RETOUR: l'indice de la dernière ligne avec au moins un chiffre après l'initialisation
int init_grille(t_grille_nos grille, t_tab_chiffres nbr_chiffres);

//Permet de générer la liste de tous les coups (couples) possibles à jouer.
//PARAM.: la grille de jeu, sa dernière ligne et la listes des coups possibles à remplir
//RETOUR: Le nombre de couples possibles répertoriés pour le prochain coup à jouer
int generer_listes_couples(const t_grille_nos grille, int dern_lig, t_liste_couples liste);

//Permet de retirer la ligne vide [no_lig] de la grille des chiffres.
//Les lignes suivantes seront toutes recopiée UNE ligne plus haut pour remplir l'espace vide.
//PARAM.: la grille de jeu et l'indice de la ligne vide à supprimer
//RETOUR: aucun
void retirer_ligne(t_grille_nos grille, int no_lig);

//Permet d'effacer (mettre à zéro) la case "pos" de la grille de jeu.
//Le nb. de chiffres de cette ligne sera aussi décrémenté (dans la colonne [0] de cette ligne)
//PARAM.: la grille de jeu et la position de la case à vider (eg. 24 == case [2][4])
//RETOUR: aucun
void effacer_chiffre(t_grille_nos grille, int pos);

//Permet de retirer (mettre à zéro) le chiffre "ch" de la liste des chiffres dispos.
//Apès ce retrait ce chiffre ne sera plus généré lors des prochaines regénérations de chiffres
//Le nb. de chiffres dispos du tableau sera aussi décrémenté (compteur dans la case [0])
//PARAM.: le chiffre à retirer et la listes des chiffres dispos
//RETOUR: retour du même chiffre "ch" si ce chiffre n'est plus présent dans le jeu, 0 sinon.
int  retirer_chiffre(int ch, t_tab_chiffres nbr_chiffres);

//Accesseur au chiffre se trouvant à la case "no_case" de la grille.
//PARAM.: la grille de jeu et la position de la case désirée (eg. 24 == case [2][4])
//RETOUR: (entier) le chiffre qui se trouve à cette position de la grille
int  get_chiffre_case(const t_grille_nos grille, int no_case);

//Accesseur au nb. de chiffres restants dans le jeu (la case [0] du tableau).
//Note: le jeu se termine lorsque cette fonction retourne 0 (plus de chiffres).
//PARAM.: la listes des chiffres dispos
//RETOUR: (entier) le nb. de chiffres encore disponibles
int  nb_chiffres_restants(const t_tab_chiffres nbr_chiffres);

//Permet de générer de nouveau chiffres alea. qui seront ajoutés à la suite des
//chiffre restants dans la grille de jeu.
//Le nombre de chiffres générés pour chaque chiffre sera ajouté à "nbr_chiffres[]".
//PARAM.: la grille de jeu, la listes des chiffres dispos et une référence à la dernière ligne
//RETOUR: aucun, mais l'indice de la dernière ligne avec au moins un chiffre sera modifié
void ajouter_chiffres(t_grille_nos grille, t_tab_chiffres nbr_chiffres, int *dern_lig);

#endif