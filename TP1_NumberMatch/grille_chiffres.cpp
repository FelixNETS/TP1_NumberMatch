// grille_chiffres.cpp
// Auteur: F�lix Nadeau et Jean-Christophe Latreille
// Date (derni�re modif.): 8/3/2026
// 
// Module de gestion et initialisation de la grille de chiffres
/**********************CONSTANTES***********************/

enum directions { S_OUEST = 1, SUD, S_EST, OUEST, MILIEU, EST, N_OUEST, NORD, N_EST };

/************ COMMANDES DE PR�PROCESSEUR **************/

#include "grille_chiffres.h"

/******************** MACROS **************************/

/*MACRO INCR�MENTE POSITION
* SI nous sommes � la colonne 9 {
* -revient � colonne 0
* -baisse d'un ligne }
* incr�mente la colonne de +1
*/

#define INC_POS(lig,col)    \
	if (col == 9) {         \
		(col) = 0;		    \
		(lig)++;		    \
	}						\
	col++

/*******************FONCTIONS PRIVEES******************/

void verifier_huit_directions(t_grille_nos grille, int ligne, int colonne,
    t_liste_couples liste);

void verifier_sens_est(t_grille_nos grille, int ligne, int colonne, t_liste_couples liste);

/********* IMPL�MENTATIONS DES FONCTIONS **************/

/*---------------------- verifier_ch_voisin() ---------------------------*/

int verifier_ch_voisin(t_grille_nos grille, int lig, int col, int a_inserer) {

	/*Boucle FOR o� i = D�CALAGE LIGNE*/
	for (int i = -1; i <= 1; i++) {

		/*Boucle FOR o� j = D�CALAGE COLONNE*/
		for (int j = -1; j <= 1; j++) {

			/*V�rification des bornes avant acc�s au tableau*/
			if (lig + i < 0 || lig + i >= MAX_LIG) continue;
			if (col + j < 1 || col + j >= NB_COL) continue;

			/*SI la valeur � ins�rer = valeurs des cases adjacentes RETOUR = 0*/
			if ((grille[lig + i][col + j] == a_inserer) && (i || j)) return 0;
		}
	}
	return 1; //si la fonction trouve aucune valeur �gale adjacente RETOUR = 1
}

/*-------------------------- init_grille() ------------------------------*/

int init_grille(t_grille_nos grille, t_tab_chiffres nbr_chiffres) {

	int lig = 0,				 // Coordonn�e y du tableau
		col = 0,				 // Coordonn�e x du tableau
		val_a_inserer = 0,		 // Valeur � ins�rer dans la grille
		qte_a_inserer = 0;		 // Quantit� de valeurs � ins�rer dans la grille

	/***************************/

	/*Boucle DO WHILE r�-essaie la g�n�ration tant que... 
	* la grille  ne contient pas chaque chiffre de 1 � 9*/

	do { 

		lig = 0;				 // R�initialisation des coordonn�es init avant chaque essai
		col = 0;				 // Sinon, chaque essai d�cale la position des valeurs

		/*R�initialisation de la grille et du tableau nbr_chiffres avant chaque essai
		* Sans cela, les valeurs r�siduelles du pr�c�dent essai corrompraient les r�sultats*/
		for (int r = 0; r < MAX_LIG; r++)
			for (int c = 0; c < NB_COL; c++)
				grille[r][c] = 0;
		for (int k = 0; k < NB_COL; k++)
			nbr_chiffres[k] = 0;

		/*D�cision al�atoire de la quantit� de valeurs � ins�rer (min = 36 ; max = 45)
		* La valeur est incr�ment�e de 1 si elle est impaire*/

		qte_a_inserer = (reel_aleatoire(4.0, 5.0) * 9);
		if (qte_a_inserer % 2) qte_a_inserer++;

		/*Boucle FOR : Ins�re une valeur dans chaque case de la grille
		* Repete pour autant de fois qu'il y a de valeurs � ins�rer*/

		for (qte_a_inserer; qte_a_inserer > 0; qte_a_inserer--) {

			INC_POS(lig, col); // Passe au prochain index de la grille

			/*Boucle DO WHILE repete tant que l'entier al�atoire g�n�r�
			* est �gal � ses voisins dans la grille*/

			do {

				val_a_inserer = entier_aleatoire(1, 9); // Gen. entier entre 1 et 9

			} while (!verifier_ch_voisin(grille, lig, col, val_a_inserer));

			grille[lig][col] = val_a_inserer;			// Insertion entier choisi

			/*Insertion de la quantit� de valeurs par ligne � la colonne 0 de la grille
			SI on arrive � la derni�re colonne OU � la derni�re valeur ins�r�e*/

			if ((col == 9) || (qte_a_inserer == 1)) grille[lig][POS_NB] = col;

			/*Remplissage du tableau de quantit� de chiffres disponibles
			* Index 0		: Incr�ment� � la premi�re insertion de chaque valeur
			* Indexes 1 � 9 : Incr�ment�s � chaque insertion de leur valeur correspondante*/

			nbr_chiffres[val_a_inserer]++;
			if (nbr_chiffres[val_a_inserer] == 1) nbr_chiffres[0]++;
		}

	} while (nbr_chiffres[0] != 9);

	return (lig + 1);
}

/*---------------------- generer_listes_couples() -----------------------*/

int generer_listes_couples(const t_grille_nos grille, int dern_lig, t_liste_couples liste) {

    int i, j;   // Indices de ligne et de colonne


    // Cet algorithme permet de passer chaque case non-vide de la grille afin de trouver tous
    // les coups possibles et de les ajouter � la liste de coups.
    for (i = 0; i <= dern_lig; i++) {   // Boucle qui passe chaque ligne non-vide
        if (grille[i][POS_NB] != CASE_VIDE) {   // Si la ligne est non-vide (pr�caution)
            for (j = POS_NB+1; j <NB_COL; j++) {    // Boucle qui passe chaque colonne
                if (grille[i][j] != CASE_VIDE) {    // Si la case est non-vide
                    verifier_huit_directions(grille, i, j, liste);
                }
            }
        }
    }

    return nb_couples(liste);   // Retourne le nombre de coups ajout�s � la liste
}

/*-------------------- verifier_huit_directions() -----------------------*/

void verifier_huit_directions(t_grille_nos grille, int ligne, int colonne,
    t_liste_couples liste) {

    int direction,  // Variable de la direction du d�placement
        lig2, col2, // Ligne et colonne ajust�e en fonction de la direction
        delta_lig, delta_col,   // Valeur de d�placement selon la direction
        chiffre_depart, chiffre_final,  // Valeurs des deux chiffres � v�rifier
        caseA, caseB;   // Valeurs � ajouter � la liste des coups

    chiffre_depart = grille[ligne][colonne];    // D�finition de la valeur de d�part

    // Boucle qui permet de v�rifier s'il y a un coup possible dans chacune des 8 directions
    // possibles (Nord, Sud, Est, Ouest, etc.)
    for (direction = S_OUEST; direction <= N_EST; direction++) {

        // D�finie la valeur du d'incr�ment du d�placement selon la direction
        switch (direction) {
        case S_OUEST:
            delta_lig = 1;
            delta_col = -1;
            break;

        case SUD:
            delta_lig = 1;
            delta_col = 0;
            break;

        case S_EST:
            delta_lig = 1;
            delta_col = 1;
            break;

        case OUEST:
            delta_lig = 0;
            delta_col = -1;
            break;

        case MILIEU:
            continue; // Case centrale, on passe � la prochaine direction

            // Cas particulier: On utilise une sous-fonction sp�ciale pour v�rifier la
            // direction "EST". Cette sous-fonction priv�e g�re tout pour l'ajout � la liste
            // de coups.
        case EST:
            verifier_sens_est(grille, ligne, colonne, liste);   // G�re le cas particulier
            // On passe � la prochaine direction puisque les prochaines �tapes sont d�j�
            // g�r�es.
            continue;

        case N_OUEST:
            delta_lig = -1;
            delta_col = -1;
            break;

        case NORD:
            delta_lig = -1;
            delta_col = 0;
            break;

        case N_EST:
            delta_lig = -1;
            delta_col = 1;
            break;
        }

        // On modifie la ligne et colonne en fonction du delta de direction
        lig2 = ligne + delta_lig;
        col2 = colonne + delta_col;

        // Conditions d'arr�t :
        // - bord gauche (col2 < 1) ou bord haut (lig2 < 0)
        // - bord droit (col2 > 9) pour les diagonales/horizontale gauche
        // - ligne compl�tement vide vers le bas (grille[lig2][POS_NB] == 0)
        while (lig2 >= 0 && lig2 < MAX_LIG &&
            col2 >= 1 && col2 <= 9 &&
            grille[lig2][POS_NB] != 0 &&
            grille[lig2][col2] == 0) {
            lig2 += delta_lig;
            col2 += delta_col;
        }

        // V�rifier que la case finale est dans les bornes
        if (lig2 < 0 || lig2 >= MAX_LIG) continue;
        if (col2 < 1 || col2 > 9)        continue;
        if (grille[lig2][POS_NB] == 0)   continue; // ligne vide
        if (grille[lig2][col2] == 0)     continue; // case vide

        chiffre_final = grille[lig2][col2];

        // V�rifier si les chiffres correspondent
        if (chiffre_depart == chiffre_final ||
            chiffre_depart + chiffre_final == 10) {
            caseA = ligne * 10 + colonne;
            caseB = lig2 * 10 + col2;

            if (!liste_contient(liste, caseA, caseB)) {
                ajouter_couple(liste, caseA, caseB);
            }
        }
    }
}

/*------------------------- verifier_sens_est() -------------------------*/

void verifier_sens_est(t_grille_nos grille, int ligne, int colonne, t_liste_couples liste) {
    int lig2 = ligne,
        col2 = colonne,
        chiffre_depart = grille[ligne][colonne],
        chiffre_final,
        caseA, caseB;

    INC_POS(lig2, col2);

    while (lig2 < MAX_LIG && grille[lig2][POS_NB] != 0 && grille[lig2][col2] == 0) {
        INC_POS(lig2, col2);
    }

    if (lig2 < MAX_LIG && grille[lig2][POS_NB] != 0 && grille[lig2][col2] != 0) {

        chiffre_final = grille[lig2][col2];

        if (chiffre_depart == chiffre_final || chiffre_depart + chiffre_final == 10) {

            caseA = ligne * 10 + colonne;
            caseB = lig2 * 10 + col2;

            if (!liste_contient(liste, caseA, caseB)) ajouter_couple(liste, caseA, caseB);
        }
    }
}

