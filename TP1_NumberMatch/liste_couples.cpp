// liste_couples.cpp		   
// Auteur: 
// Date:
// 
// Module qui gère la liste des coups possibles à jouer.
#include "liste_couples.h"

/************************* les FONCTIONS PUBLIQUES ***************************/

//remise à zéro de la liste des couples possibles (NOTE: fonction donnée aux élèves!)
void init_liste_couples(t_liste_couples liste) {
	//remise à VIDE du tableau (NOTE: l'utilisation des constantes ici est OBLIGATOIRE!)
	liste[LIG_INFOS][COL_TAILLE] = MAX_COUPLES;
	liste[LIG_INFOS][COL_NBELEM] = 0;
}

