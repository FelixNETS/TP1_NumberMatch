// liste_couples.cpp
// Auteur: Jean-Christophe Latreille
// Date: 25 février 2026
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

int nb_couples(const t_liste_couples liste) {
    return liste[LIG_INFOS][COL_NBELEM];
}

int ajouter_couple(t_liste_couples liste, int caseA, int caseB) {
    int nb_elements = nb_couples(liste);

    if (nb_elements < MAX_COUPLES) {
        liste[LIG_INFOS + 1 + nb_elements][COL_TAILLE] = caseA;
        liste[LIG_INFOS + 1 + nb_elements][COL_NBELEM] = caseB;
        liste[LIG_INFOS][COL_NBELEM]++;
        return 1;
    }

    return 0;
}

int  liste_contient(t_liste_couples liste, int caseA, int caseB) {
    int i,
        nb_elements = nb_couples(liste);

    for (i = LIG_INFOS + 1; i <= nb_elements; i++) {
        if ((liste[i][COL_TAILLE] == caseA && liste[i][COL_NBELEM] == caseB) ||
            (liste[i][COL_TAILLE] == caseB && liste[i][COL_NBELEM] == caseA)) return 1;
    }

    return 0;
}

void choix_couple_alea(const t_liste_couples liste, int* caseA, int* caseB) {
    int nb_elements = nb_couples(liste),
        i = entier_aleatoire(LIG_INFOS + 1, nb_elements);
    *caseA = liste[i][COL_TAILLE];
    *caseB = liste[i][COL_NBELEM];
}

/*===========================================================*/
/*                       MAIN DE TEST                        */
/*===========================================================*/

#if (TEST_LISTE_COUPLES == 1)

void test_init_liste_couples();

void test_nb_couples();

void test_ajouter_couple();

void test_liste_contient();

void test_choix_couple_alea();

int main(void) {
    printf("========================================\n");
    printf("           TESTS UNITAIRES\n");
    printf("========================================\n");

    // Appel des 5 sous-programmes de test
    test_init_liste_couples();
    test_nb_couples();
    test_ajouter_couple();
    test_liste_contient();
    test_choix_couple_alea();

    printf("\n========================================\n");
    printf("  TOUS LES TESTS ONT REUSSI!\n");
    printf("  Total: 25 tests executes\n");
    printf("========================================\n");

    return 0;
}

/*===========================================================*/
/*        SOUS-PROGRAMME DE TEST: init_liste_couples         */
/*===========================================================*/
void test_init_liste_couples(void) {
    printf("\n=== TESTS DE init_liste_couples() ===\n");

    t_liste_couples liste;
    init_liste_couples(liste);

    // Test 1: COL_TAILLE doit etre MAX_COUPLES
    assert(liste[LIG_INFOS][COL_TAILLE] == MAX_COUPLES);
    printf("  Test 1 reussi: COL_TAILLE = MAX_COUPLES apres init\n");

    // Test 2: COL_NBELEM doit etre 0
    assert(liste[LIG_INFOS][COL_NBELEM] == 0);
    printf("  Test 2 reussi: COL_NBELEM = 0 apres init\n");

    // Test 3: nb_couples retourne 0 apres init
    assert(nb_couples(liste) == 0);
    printf("  Test 3 reussi: nb_couples() retourne 0 apres init\n");

    // Test 4: Re-init apres ajout remet nb_couples a 0
    ajouter_couple(liste, 11, 22);
    init_liste_couples(liste);
    assert(nb_couples(liste) == 0);
    printf("  Test 4 reussi: re-init apres ajout remet nb_couples a 0\n");

    // Test 5: Re-init remet aussi COL_TAILLE a MAX_COUPLES
    assert(liste[LIG_INFOS][COL_TAILLE] == MAX_COUPLES);
    printf("  Test 5 reussi: re-init conserve COL_TAILLE = MAX_COUPLES\n");

    printf(">>> init_liste_couples: TOUS LES TESTS REUSSIS\n");
}

/*===========================================================*/
/*            SOUS-PROGRAMME DE TEST: nb_couples             */
/*===========================================================*/

void test_nb_couples(void) {
    printf("\n=== TESTS DE nb_couples() ===\n");

    t_liste_couples liste;
    init_liste_couples(liste);

    // Test 1: Retourne 0 apres init
    assert(nb_couples(liste) == 0);
    printf("  Test 1 reussi: 0 element apres init\n");

    // Test 2: Retourne 1 apres 1 ajout
    ajouter_couple(liste, 11, 22);
    assert(nb_couples(liste) == 1);
    printf("  Test 2 reussi: 1 element apres 1 ajout\n");

    // Test 3: Retourne 3 apres 2 ajouts supplementaires
    ajouter_couple(liste, 33, 44);
    ajouter_couple(liste, 55, 66);
    assert(nb_couples(liste) == 3);
    printf("  Test 3 reussi: 3 elements apres 3 ajouts\n");

    // Test 4: Ne change pas si on reinitialise pas
    assert(nb_couples(liste) == 3);
    printf("  Test 4 reussi: nb_couples stable sans modification\n");

    // Test 5: Retourne MAX_COUPLES quand la liste est pleine
    int i;
    init_liste_couples(liste);
    for (i = 0; i < MAX_COUPLES; i++) {
        ajouter_couple(liste, i, i + 1);
    }
    assert(nb_couples(liste) == MAX_COUPLES);
    printf("  Test 5 reussi: nb_couples = MAX_COUPLES quand liste pleine\n");

    printf(">>> nb_couples: TOUS LES TESTS REUSSIS\n");
}

/*===========================================================*/
/*          SOUS-PROGRAMME DE TEST: ajouter_couple           */
/*===========================================================*/
void test_ajouter_couple(void) {
    printf("\n=== TESTS DE ajouter_couple() ===\n");

    t_liste_couples liste;
    int i, res;
    init_liste_couples(liste);

    // Test 1: Retourne 1 lors d'un ajout valide
    res = ajouter_couple(liste, 11, 99);
    assert(res == 1);
    printf("  Test 1 reussi: retour 1 lors d'un ajout valide\n");

    // Test 2: nb_couples s'incremente apres l'ajout
    assert(nb_couples(liste) == 1);
    printf("  Test 2 reussi: nb_couples = 1 apres l'ajout\n");

    // Test 3: Les valeurs de caseA et caseB sont correctement stockees
    assert(liste[LIG_INFOS + 1][COL_TAILLE] == 11);
    assert(liste[LIG_INFOS + 1][COL_NBELEM] == 99);
    printf("  Test 3 reussi: caseA et caseB stockes au bon index\n");

    // Test 4: Ajout de MAX_COUPLES elements reussit
    init_liste_couples(liste);
    for (i = 0; i < MAX_COUPLES; i++) {
        res = ajouter_couple(liste, i, i + 1);
        assert(res == 1);
    }
    printf("  Test 4 reussi: ajout de MAX_COUPLES elements reussi\n");

    // Test 5: Retourne 0 quand la liste est pleine
    res = ajouter_couple(liste, 999, 888);
    assert(res == 0);
    printf("  Test 5 reussi: retour 0 quand la liste est pleine\n");

    printf(">>> ajouter_couple: TOUS LES TESTS REUSSIS\n");
}

/*===========================================================*/
/*          SOUS-PROGRAMME DE TEST: liste_contient           */
/*===========================================================*/
void test_liste_contient(void) {
    printf("\n=== TESTS DE liste_contient() ===\n");

    t_liste_couples liste;
    init_liste_couples(liste);
    ajouter_couple(liste, 11, 22);
    ajouter_couple(liste, 33, 44);

    // Test 1: Couple present dans l'ordre d'ajout
    assert(liste_contient(liste, 11, 22) == 1);
    printf("  Test 1 reussi: couple present dans l'ordre original\n");

    // Test 2: Couple present dans l'ordre inverse
    assert(liste_contient(liste, 22, 11) == 1);
    printf("  Test 2 reussi: couple present dans l'ordre inverse\n");

    // Test 3: Deuxieme couple present
    assert(liste_contient(liste, 33, 44) == 1);
    printf("  Test 3 reussi: deuxieme couple present\n");

    // Test 4: Couple absent retourne 0
    assert(liste_contient(liste, 11, 99) == 0);
    printf("  Test 4 reussi: couple absent retourne 0\n");

    // Test 5: Liste vide ne contient rien
    init_liste_couples(liste);
    assert(liste_contient(liste, 11, 22) == 0);
    printf("  Test 5 reussi: liste vide ne contient rien\n");

    printf(">>> liste_contient: TOUS LES TESTS REUSSIS\n");
}

/*===========================================================*/
/*        SOUS-PROGRAMME DE TEST: choix_couple_alea          */
/*===========================================================*/
void test_choix_couple_alea(void) {
    printf("\n=== TESTS DE choix_couple_alea() ===\n");

    t_liste_couples liste;
    int caseA, caseB;
    init_liste_couples(liste);
    ajouter_couple(liste, 11, 22);
    ajouter_couple(liste, 33, 44);
    ajouter_couple(liste, 55, 66);

    // Test 1: Le couple choisi appartient a la liste (1er appel)
    choix_couple_alea(liste, &caseA, &caseB);
    assert(liste_contient(liste, caseA, caseB) == 1);
    printf("  Test 1 reussi: 1er couple aleatoire appartient a la liste\n");

    // Test 2: Le couple choisi appartient a la liste (2e appel)
    choix_couple_alea(liste, &caseA, &caseB);
    assert(liste_contient(liste, caseA, caseB) == 1);
    printf("  Test 2 reussi: 2e couple aleatoire appartient a la liste\n");

    // Test 3: Le couple choisi appartient a la liste (3e appel)
    choix_couple_alea(liste, &caseA, &caseB);
    assert(liste_contient(liste, caseA, caseB) == 1);
    printf("  Test 3 reussi: 3e couple aleatoire appartient a la liste\n");

    // Test 4: caseA retourne est non nul
    assert(caseA != 0);
    printf("  Test 4 reussi: caseA retourne est non nul\n");

    // Test 5: caseB retourne est non nul
    assert(caseB != 0);
    printf("  Test 5 reussi: caseB retourne est non nul\n");

    printf(">>> choix_couple_alea: TOUS LES TESTS REUSSIS\n");
}

#endif