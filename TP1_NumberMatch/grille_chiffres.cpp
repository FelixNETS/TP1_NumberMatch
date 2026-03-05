// grille_chiffres.cpp
// Auteur: Félix Nadeau
// Date (dernière modif.): 5/3/2026
// 
// Module de gestion et initialisation de la grille de chiffres


/************ COMMANDES DE PRÉPROCESSEUR **************/

#include "grille_chiffres.h"

/******************** MACROS **************************/

/*MACRO INCRÉMENTE POSITION
* SI nous sommes à la colonne 9 {
* -revient à colonne 0
* -baisse d'un ligne }
* incrémente la colonne de +1
*/

#define INC_POS(lig,col)    \
	if (*(col) == 9) {      \
		(*(col)) = 0;		\
		(*(lig))++;		    \
	}						\
	(*(col))++

/********* IMPLÉMENTATIONS DES FONCTIONS **************/

/*---------------------- verifier_ch_voisin() ---------------------------*/

int verifier_ch_voisin(t_grille_nos grille, int lig, int col, int a_inserer) {

	/*Boucle FOR où i = DÉCALAGE LIGNE*/
	for (int i = -1; i <= 1; i++) {

		/*Boucle FOR où j = DÉCALAGE COLONNE*/
		for (int j = -1; j <= 1; j++) {

			/*SI la valeur à insérer = valeurs des cases adjacentes RETOUR = 0*/
			if ((grille[lig + i][col + j] == a_inserer) && (i || j)) return 0;
		}
	}
	return 1; //si la fonction trouve aucune valeur égale adjacente RETOUR = 1 
}

/*-------------------------- init_grille() ------------------------------*/

int init_grille(t_grille_nos grille, t_tab_chiffres nbr_chiffres) {

	int lig = 0,				 // Coordonnée y du tableau
		col = 0,				 // Coordonnée x du tableau
		val_a_inserer = 0,		 // Valeur à insérer dans la grille
		qte_a_inserer = 0;		 // Quantité de valeurs à insérer dans la grille

	/***************************/

	/*Boucle DO WHILE ré-essaie la génération tant que... 
	* la grille  ne contient pas chaque chiffre de 1 à 9*/

	do { 

		lig = 0;				 // Réinitialisation des coordonnées init avant chaque essai
		col = 0;				 // Sinon, chaque essai décale la position des valeurs

		/*Décision aléatoire de la quantité de valeurs à insérer (min = 36 ; max = 45)
		* La valeur est incrémentée de 1 si elle est impaire*/

		qte_a_inserer = (reel_aleatoire(4.0, 5.0) * 9);
		if (qte_a_inserer % 2) qte_a_inserer++;

		/*Boucle FOR : Insère une valeur dans chaque case de la grille
		* Repete pour autant de fois qu'il y a de valeurs à insérer*/

		for (qte_a_inserer; qte_a_inserer > 0; qte_a_inserer--) {

			INC_POS(&lig, &col); // Passe au prochain index de la grille

			/*Boucle DO WHILE repete tant que l'entier aléatoire généré
			* est égal à ses voisins dans la grille*/

			do {

				val_a_inserer = entier_aleatoire(1, 9); // Gen. entier entre 1 et 9

			} while (!verifier_ch_voisin(grille, lig, col, val_a_inserer));

			grille[lig][col] = val_a_inserer;			// Insertion entier choisi

			/*Insertion de la quantité de valeurs par ligne à la colonne 0 de la grille
			SI on arrive à la dernière colonne OU à la dernière valeur insérée*/

			if ((col == 9) || (qte_a_inserer == 1)) grille[lig][POS_NB] = col;

			/*Remplissage du tableau de quantité de chiffres disponibles
			* Index 0		: Incrémenté à la première insertion de chaque valeur
			* Indexes 1 à 9 : Incrémentés à chaque insertion de leur valeur correspondante*/

			nbr_chiffres[val_a_inserer]++;
			if (nbr_chiffres[val_a_inserer] == 1) nbr_chiffres[0]++;
		}

	} while (nbr_chiffres[0] != 9);

	return (lig + 1);
}