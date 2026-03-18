// gestion_jeu.cpp
// auteur: F�lix Nadeau
// date (derni�re modif.): 16/3/2026
// 
// FICHIER PROGRAMME
// gestion g�n�rale du fonctionnement 
// validation des coups entr�s
// gestion ds points

#define _CRT_SECURE_NO_WARNINGS

/******************** LIBRAIRIES INCLUSES **********************/


#include "gestion_jeu.h"


/************************* FONCTIONS ****************************/

/*---------------------- saisie_case() -------------------------*/
//Saisit et valide l'adresse d'une case (ex. "A1") ou un code-commande ("++", "??", "XX").
//Rep�te la demande tant que la saisie n'est pas jug�e valide.
//NOTE: fonction priv�e au module gestion_jeu.cpp
//PARAM.: la derni�re ligne active de la grille, le num�ro de la saisie (1 ou 2)
//RETOUR: la position-case valide (entier) ou un code-commande (CODE_QUITTER/AIDE/CHIFFRES)

int saisie_case(int derniere_lig, int numero_saisie) {

	bool valide = 0,    // indicateur : 1 si la saisie est valid�e, 0 sinon
		decalage = 0;   // vaut 1 si la ligne a 2 chiffres (saisie 3 car.); 0 sinon

	int position = 0;   // position encod�e (lig*10+col) calcul�e � partir de la saisie

	char buff[10];      // tampon de 10 caract�res pour stocker la saisie utilisateur
	strcpy(buff, "");   // initialisation du tampon � cha�ne vide


	/*BOULCLE WHILE Validation de la saisie entr�e
	* continue tant que la saisie n'est pas d�termin�e valide */

	while (!valide) {

		position = 0;	// r�-initialisation de la position
		decalage = 0;	// r�-initialisation du d�calage d�cimal

		demander_saisie(numero_saisie);		//Saisie du coup
		scanf("%s", buff);

		// stockage de la longueur de saisie dans une variable
		// active le d�calage d�cimal SI la saisie est 3 CHAR de long
		// (car �a veut dire que la ligne saisie a 2 digits)
		int longueur = strlen(buff); // nb. de caract�res saisis par l'utilisateur
		if (longueur == 3) decalage = 1;

		// force les lettres saisies en majuscule
		// (inclut buff[1] au cas o� on saisi XX)
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

		// cas 3: chiffre 1 invalide (valide = 1 � 9)
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

		valide = true;	// la postition est valid�e, la boucle termine
	}

	return position;	// retour de la position valide saisie
}

/*--------------------------- valider_coup() ----------------------------*/

int valider_coup(t_liste_couples liste, int derniere_lig, int* caseA, int* caseB) {

	bool couple_valide = 0; // indicateur : 1 si le couple est valide, 0 sinon
	int i;                  // indice de parcours de la liste des couples

	// Boucle WHILE de validation. r�p�te tant que le joueur
	// n'entre pas un coup valide OU un des codes sp�ciaux

	while (!couple_valide) {

		*caseA = saisie_case(derniere_lig, 1);	// demande du 1er coup

		// la fonction retourne 0 si le joueur entre un des codes
		if (*caseA == CODE_CHIFFRES || *caseA == CODE_AIDE || *caseA == CODE_QUITTER) {
			return 0;
		}

		*caseB = saisie_case(derniere_lig, 2);	// demande du 2ieme coup

		// Boucle FOR v�rification de la liste des couples valides

		for (i = 1; i <= liste[0][1]; i++) {

			// si le couple entr� est dans la liste des couples valides
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

/*--------------------------- jouer_coup() ------------------------------*/

int jouer_coup(t_grille_nos grille, t_tab_chiffres nbr_chiffres,
	int* derniere_lig, int caseA, int caseB) {

	int points = 0,     // points obtenus pour le retrait du couple de cases
		pts_lignes = 0, // points suppl�mentaires pour chaque ligne vide retir�e

		colA,           // indice de colonne de la case A (extrait de caseA)
		colB,           // indice de colonne de la case B (extrait de caseB)

		ligA,           // indice de ligne de la case A (extrait de caseA)
		ligB;           // indice de ligne de la case B (extrait de caseB)

	colA = caseA % 10;			// extrait la colonne A de la position A
	colB = caseB % 10;			// extrait la colonne B de la position B

	ligA = caseA / 10;			// extrait la ligne A de la position A
	ligB = caseB / 10;			// extrait la ligne B de la position B

	char mess_lig[50],  // tampon pour le message de ligne(s) retir�e(s)
		mess_ret[50];   // tampon pour le message de chiffre retir�

	// attribution des points par coup. 
	// si les points sont coll�s, on attribue 1 point
	// si les points sont s�par�s de cases vides, on attribue 4 points
	if ((abs(colA - colB) <= 1) && (abs(ligA - ligB) <= 1)) {
		points = PTS_COUPLE_VOISIN;
	}
	else {
		points = PTS_COUPLE_SEPARE;
	}

	// affichage des points gagn�s pour le coup jou�
	mess_points(points);

	// gestion du tableau nbr_chiffres et retrait de la case dans la grille
	// si retirer_chiffre = non-z�ro, retire le chiffre et affiche message de retrait
	// puis le chiffre dans la case de la grille est effac�
	if (retirer_chiffre(grille[ligA][colA], nbr_chiffres)) {
		sprintf(mess_ret, "chiffre %d retire", grille[ligA][colA]);
		message(mess_ret);
	}
	effacer_chiffre(grille, caseA);

	if (retirer_chiffre(grille[ligB][colB], nbr_chiffres)) {
		sprintf(mess_ret, "chiffre %d retire", grille[ligB][colB]);
		message(mess_ret);
	}

	effacer_chiffre(grille, caseB);

	// on veut que la position caseA soit plus grande que caseB (caseA > caseB)
	// donc, nous les permutons si c'est le cas inverse
	if (ligA < ligB) {
		int temp = ligA;    // variable temporaire pour la permutation de ligA et ligB
		ligA = ligB;
		ligB = temp;
	}

	if (grille[ligA][0] == 0) {
		pts_lignes += PTS_LIGNE_RETIREE;
		retirer_ligne(grille, ligA);
		(*derniere_lig)--;
	}

	if ((ligA != ligB) && (grille[ligB][0] == 0)) {
		pts_lignes += PTS_LIGNE_RETIREE;
		retirer_ligne(grille, ligB);
		(*derniere_lig)--;
	}

	// si pts_lignes est non-z�ro (indiquant qu'uen a �t� retir�e) 
	// on evoie un message de ligne retir�e et les points gagn�s
	if (pts_lignes) {
		sprintf(mess_lig, "%d lignes retirees! +%d points", pts_lignes / 10, pts_lignes);
		message(mess_lig);
	}

	return (points + pts_lignes);		// on retourne la somme des points
}

/*------------------------- afficher_indice() ---------------------------*/
void afficher_indice(t_grille_nos grille, int *caseA, int *caseB) {
	int colA = (*caseA) % 10,  // colonne de la case A (extrait de caseA)
		ligA = (*caseA) / 10,  // ligne de la case A (extrait de caseA)
		valA = grille[ligA][colA]; // valeur du chiffre se trouvant en case A

	int	colB = (*caseB) % 10,  // colonne de la case B (extrait de caseB)
		ligB = (*caseB) / 10,  // ligne de la case B (extrait de caseB)
		valB = grille[ligB][colB]; // valeur du chiffre se trouvant en case B

	char indA = COL_A_LETTRE(colA), // lettre correspondant � la colonne de la case A
		 indB = COL_A_LETTRE(colB); // lettre correspondant � la colonne de la case B

	char mess[50];  // tampon pour le message texte du coup sugg�r�

	sprintf(mess, "Jouez les cases %c%d et %c%d", indA, ligA + 1, indB, ligB + 1);

	message(mess);

	afficher_couple(colA, ligA, valA, colB, ligB, valB);
}