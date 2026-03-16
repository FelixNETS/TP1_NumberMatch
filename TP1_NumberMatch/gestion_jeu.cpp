// gestion_jeu.cpp
// auteur: Félix Nadeau
// date (dernière modif.): 13/3/2026
// 
// FICHIER PROGRAMME
// gestion générale du fonctionnement 
// validation des coups entrés
// gestion ds points

/******************** LIBRAIRIES INCLUSES **********************/


#include "gestion_jeu.h"


/************************* FONCTIONS ****************************/

/*---------------------- saisie_case() -------------------------*/

// validation & analyse de la commande saisie par le joueur 
// fonction privée au module gestion_jeu.cpp
// PARAMS: la dernière ligne de la grille et le # de la saisie actuelle
// RETOUR: soit un des code spéciaux ou la position saisie

int saisie_case(int derniere_lig, int numero_saisie) {

	bool valide = 0,	// validation de la saisie
		 decalage = 0;	// sert à décaler un chiffre d'une pos. décimale

	int position = 0;	// posisiton correspondante de la saisie

	char buff[10];		// string de longueur 10. store la saisie
	strcpy(buff, "");	// initialisation du string


	/*BOULCLE WHILE Validation de la saisie entrée
	* continue tant que la saisie n'est pas déterminée valide */

	while (!valide) {

		position = 0;	// ré-initialisation de la position
		decalage = 0;	// ré-initialisation du décalage décimal

		demander_saisie(numero_saisie);		//Saisie du coup
		scanf("%s", buff);

		// storage de la longueur de saisie dans une variable
		// active le décalage décimal SI la saisie est 3 CHAR de long
		// (car ça veut dire que la ligne saisie a 2 digits)
		int longueur = strlen(buff);
		if (longueur == 3) decalage = 1;

		// force les lettres saisies en majuscule
		// (inclut buff[1] au cas où on saisi XX)
		buff[0] = toupper(buff[0]);
		buff[1] = toupper(buff[1]);


		/*SAISIE DES CODES (s'il y a lieu)*/

		if (strcmp(buff, "++") == 0) return CODE_CHIFFRES;	// code CHIFFRES
		if (strcmp(buff, "??") == 0) return CODE_AIDE;		// code AIDE
		if (strcmp(buff, "XX") == 0) return CODE_QUITTER;	// code QUITTER


		/*LES CAS D'ERREUR*/

		// cas 1: saisie trop longue (>3)
		if (longueur > COUP_MAXLONG) {
			mess_erreur("saisie trop longue! max 3 char.");
			continue;
		}

		// cas 2: colonne invalide (valide = lettre entre A et I)
		if (!(buff[0] >= 'A' && buff[0] <= 'I')) {
			mess_erreur("colonne inexistante!");
			continue;
		}

		// cas 3: chiffre 1 invalide (valide = 1 à 9)
		if (!(buff[1] > '0' && buff[1] <= '9')) {
			mess_erreur("ligne inexistante!");
			continue;
		}

		// cas 4: chiffre 2 invalide (JUSTE SI SAISIE = 3 DE LONG)
		if (longueur == 3 && !(buff[2] >= '0' && buff[2] <= '9')) {
			mess_erreur("ligne inexistante!");
			continue;
		}

		
		/*CALCUL DE LA POSITION SELON LA SAISIE*/

		// la valeur decalage vaut 1 quand la saisie est 3 CHAR de long
		// et vaut 0 lorsque non.
		// quand elle vaut 1, elle fait buff[1] x 10 et y ajoute buff[2]
		
		position = (CHIFFRES_A_VAL(buff[1]) * (pow(10, decalage))) - 1;
		position += (CHIFFRES_A_VAL(buff[2]) * decalage);
		position = (position * 10) + LETTRE_A_COL(buff[0]);

		// valide que la position fait partie de la grille 
		if (position > ((derniere_lig * 10) - 1)) {
			mess_erreur("coup hors grille!");
			continue;
		}
		
		valide = true;	// la postition est validée, la boucle termine
	}

	return position;	// retour de la position valide saisie
}

/*---------------------- valider_coup() ------------------------*/

int valider_coup(t_liste_couples liste, int derniere_lig, int* caseA, int* caseB) {

	bool couple_valide = 0;		// 0 = couple invalide; 1 = couple valide

	// Boucle WHILE de validation. répète tant que le joueur
	// n'entre pas un coup valide OU un des codes spéciaux

	while (!couple_valide) {

		*caseA = saisie_case(derniere_lig, 1);	// demande du 1er coup

		// la fonction retourne 0 si le joueur entre un des codes
		if (*caseA == CODE_CHIFFRES || *caseA == CODE_AIDE || *caseA == CODE_QUITTER) {
			return 0;
		}

		*caseB = saisie_case(derniere_lig, 2);	// demande du 2ieme coup

		// Boucle FOR vérification de la liste des couples valides

		for (int i = 1; i <= liste[0][1]; i++) {

			// si le couple entré est dans la liste des couples valides
			// PEU IMPORTE L'ORDRE on valide le couple et sort du FOR
			if ((*caseA == liste[i][0]) && (*caseB == liste[i][1])) {
				couple_valide = 1;
				break;
			}

			if ((*caseA == liste[i][1]) && (*caseB == liste[i][0])) {
				couple_valide = 1;
				break;
			}
		}

		// affiche message d'erreur SI le couple est invalide
		if (!couple_valide) mess_erreur("couple invalide!");
	}

	return 1;
}

/*----------------------- jouer_coup() -------------------------*/

int jouer_coup(t_liste_couples grille, t_tab_chiffres nbr_chiffres,
	int* derniere_lig, int caseA, int caseB) {

	int points = 0,				// points pour le coup joué
		pts_lignes = 0,			// points pour effacer une ligne

		colA,					// colonne de la case A
		colB,					// colonne de la case B

		ligA,					// ligne de la case A
		ligB;					// ligne de la case B

	colA = caseA % 10;			// extrait la colonne A de la position A
	colB = caseB % 10;			// extrait la colonne B de la position B

	ligA = (caseA / 10) + 1;	// extrait la ligne A de la position A
	ligB = (caseB / 10) + 1;	// extrait la ligne B de la position B

	// attribution des points par coup. 
	// si les points sont collés, on attribue 1 point
	// si les points sont séparés de cases vides, on attribue 4 points
	if ((abs(colA - colB) <= 1) && (abs(ligA - ligB) <= 1)) {
		points = PTS_COUPLE_VOISIN;
	}
	else {
		points = PTS_COUPLE_SEPARE;
	}

	// affichage des points gagnés pour le coup joué
	mess_points(points);

	// gestion du tableau nbr_chiffres et retrait de la case dans la grille
	// si retirer_chiffre = non-zéro, retire le chiffre et affiche message de retrait
	// puis le chiffre dans la case de la grille est effacé
	if (retirer_chiffre(grille[ligA][colA], nbr_chiffres)) message("chiffre retiré");//TEMPORAIRE***
	effacer_chiffre(grille, caseA);

	if (retirer_chiffre(grille[ligB][colB], nbr_chiffres)) message("chiffre retiré");//TEMPORAIRE***
	effacer_chiffre(grille, caseB);

	// on veut que la position caseA soit plus grande que caseB (caseA > caseB)
	// donc, nous les permutons si c'est le cas inverse
	if (caseA < caseB) {
		int temp = caseA;
		caseA = caseB;
		caseB = temp;
	}

	// validation lignes vides, boucles FOR vérifient chaque colonne dans une ligne
	// la boucle arrête dès qu'elle trouve une valeur non-zéro dans la ligne
	// si elle se rend à la derière colonne, on ajoute 10 pts, et on retire une ligne
	for (int i = 1; i < 10; i++) {		// boucle pour position A
		if (grille[ligA][i]) break;
		if (i == 9) {
			pts_lignes += PTS_LIGNE_RETIREE;
			retirer_ligne(grille, ligA);
			*derniere_lig--;
		}
	}

	if (ligA != ligB) {
		for (int i = 1; i < 10; i++) {	// boucle pour position B
			if (grille[ligB][i]) break;
			if (i == 9) {
				pts_lignes += PTS_LIGNE_RETIREE;
				retirer_ligne(grille, ligB);
				derniere_lig--;
			}
		}
	}

	// si pts_lignes est non-zéro (indiquant qu'uen a été retirée) 
	// on evoie un message de ligne retirée et les points gagnés
	if (pts_lignes) {
		message("n lig retirees. +n points!!!");//TEMPORAIRE***
	}

	return (points + pts_lignes);		// on retourne la somme des points
}