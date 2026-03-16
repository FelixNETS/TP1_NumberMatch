// gestion_jeu.cpp
// auteur: Félix Nadeau
// date (dernière modif.): 13/3/2026
// 
// FICHIER PROGRAMME
// programme principal
// appels aux autres programmes

/******************** LIBRAIRIES INCLUSES **********************/


#include "gestion_jeu.h"


/************************** FONCTION ****************************/

/*-------------------------- main() ----------------------------*/

int main(void) {
	
	t_grille_nos grille;
	t_liste_couples liste_couples;
	t_tab_chiffres nbr_chiffres = {0,0,0,0,0,0,0,0,0,0};

	int derniere_lig,
		caseA,
		caseB,
		score = 0,
		quitter = 0;

	init_rand();
	derniere_lig = init_grille(grille, liste_couples);

	//AFFICHAGES ICI, BESOIN PARTIE 6

	do {
		init_liste_couples(liste_couples);

		if (!generer_listes_couples(grille, derniere_lig, liste_couples)) break;
		score += jouer_coup(grille, nbr_chiffres, &derniere_lig, caseA, caseB);

		//AFFICHAGES ICI, BESOIN PARTIE 6

	} while (!quitter && nbr_chiffres[0] && liste_couples && liste_couples[0][1]);

	message("Partie terminée. n points!!!"); //TEMPORAIRE***

	system("pause");
	return EXIT_SUCCESS;
}