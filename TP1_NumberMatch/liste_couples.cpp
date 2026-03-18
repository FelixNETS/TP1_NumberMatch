// liste_couples.cpp
// Auteur: Jean-Christophe Latreille
// Date (derni�re modif.): 16/3/2026
// 
// Module qui g�re la liste des coups possibles � jouer.
#include "liste_couples.h"

/************************* les FONCTIONS PUBLIQUES ***************************/

//remise � z�ro de la liste des couples possibles (NOTE: fonction donn�e aux �l�ves!)
void init_liste_couples(t_liste_couples liste) {
    //remise � VIDE du tableau (NOTE: l'utilisation des constantes ici est OBLIGATOIRE!)
    liste[LIG_INFOS][COL_TAILLE] = MAX_COUPLES;
    liste[LIG_INFOS][COL_NBELEM] = 0;
}

int nb_couples(t_liste_couples liste) {
    return liste[LIG_INFOS][COL_NBELEM];   // retourne le compteur d'elements actuels
}

int ajouter_couple(t_liste_couples liste, int caseA, int caseB) {
    int nb_elements = nb_couples(liste);    // nb. de couples d�j� pr�sents dans la liste

    if (nb_elements < MAX_COUPLES) {
        // insere le nouveau couple a la prochaine position libre (apres la ligne d'infos)
        liste[LIG_INFOS + 1 + nb_elements][COL_TAILLE] = caseA;
        liste[LIG_INFOS + 1 + nb_elements][COL_NBELEM] = caseB;
        liste[LIG_INFOS][COL_NBELEM]++;     // incremente le compteur d'elements
        return 1;
    }

    return 0;   // liste pleine, ajout impossible
}

int  liste_contient(t_liste_couples liste, int caseA, int caseB) {
    int i,                              // indice de parcours de la liste
        nb_elements = nb_couples(liste); // nb. de couples pr�sents dans la liste

    // parcourt tous les couples et verifie dans les deux sens (caseA-caseB ou caseB-caseA)
    for (i = LIG_INFOS + 1; i <= nb_elements; i++) {
        if ((liste[i][COL_TAILLE] == caseA && liste[i][COL_NBELEM] == caseB) ||
            (liste[i][COL_TAILLE] == caseB && liste[i][COL_NBELEM] == caseA)) return 1;
    }

    return 0;   // couple absent de la liste
}

void choix_couple_alea(t_liste_couples liste, int* caseA, int* caseB) {
    int nb_elements = nb_couples(liste),    // nb. de couples pr�sents dans la liste
        i = entier_aleatoire(LIG_INFOS + 1, nb_elements); // indice al�atoire dans la liste
    *caseA = liste[i][COL_TAILLE];
    *caseB = liste[i][COL_NBELEM];
}
