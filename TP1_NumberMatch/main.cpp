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

	t_grille_nos grille;				// grille de jeu	
	t_liste_couples liste_couples;		// liste des couples valides
	t_tab_chiffres nbr_chiffres =		// qté de chaque chiffre dispo
	{ 0,0,0,0,0,0,0,0,0,0 };

	int derniere_lig,					// dernière ligne de la grille
		caseA = 0,						// premiere saisie
		caseB = 0,						// deuxième saisie
		score = 0,						// pointage du joueur
		quitter = 0,					// code special
		regen = 0,
		nb_regen = 3;

	// initialisation de la gen. aleatoire
	init_rand();

	// initialisation de la grille de jeu, actualise de la derniere ligne
	derniere_lig = init_grille(grille, nbr_chiffres);

	// affichage du texte d'instruction
	afficher_instructions();

	// affichages du jeu (textes info. et grille)
	afficher_infos_jeu(nbr_chiffres, score);
	afficher_grille(grille, derniere_lig);

	// boucle DO WHILE de jeu. repete tant que la partie continue
	do {

		// actualise la liste des couples valides
		init_liste_couples(liste_couples);

		// on sort de la boucle s'il ne reste plus de couples valides
		// ou si on recoit un code spécial (TEMPORAIRE)
		// valider coup stall tant qu'on entre pas un coup valide
		if (generer_listes_couples(grille, derniere_lig, liste_couples)) {
			if (valider_coup(liste_couples, derniere_lig, &caseA, &caseB == 1)) {
				score += jouer_coup(grille, nbr_chiffres, &derniere_lig, caseA, caseB);
			}
			else if (caseA == CODE_CHIFFRES)
			{
				if (nb_regen) regen = 1;
				else message("il ne vous reste plus de regen!");
			}
		}

		if (regen || (!liste_couples[0][1] && nb_regen)) {
			ajouter_chiffres(grille, nbr_chiffres, &derniere_lig);
			init_liste_couples(liste_couples);
			generer_listes_couples(grille, derniere_lig, liste_couples);
			regen = 0;
			nb_regen--;
			mess_num("il vous reste %d regen.", nb_regen, 0, 15);
		}

		// actualise les affichages du jeu (textes info. et grille)
		afficher_infos_jeu(nbr_chiffres, score);
		afficher_grille(grille, derniere_lig);

		//repete tant qu'on ne quitte pas et qu'il reste des coups a jouer
	} while (!quitter && liste_couples[0][1]);

	mess_fin("PARTIE TERMINEE! score: %d pts", score);

	system("pause");
	return EXIT_SUCCESS;
}