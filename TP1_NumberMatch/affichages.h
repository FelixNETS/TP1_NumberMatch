// affichages.h			  (*** ÉCRIRE les 4 premières fonctions ***)
// Auteur:    
// Date:
// 
// Module qui gère toutes les fonctions d'affichages du programme pour la grille, 
// les numéros dispos, le score et messages.  Tous les affichages-écran sont définies ici.
#ifndef LIG_GRILLE

#include "grille_chiffres.h"    //va aussi inclure le module "liste_couples.h"

//les décalages pour le coin sup. gauche de l'affichage de la grille
#define LIG_GRILLE  5
#define COL_GRILLE  40

//les autres décalages-lignes pour les différents messages à afficher
#define LIG_POINTS   0					//pos-ligne pour l'affichage des points accumulés
#define LIG_CHIFFRES 1					//pos-ligne pour l'affichage de chiffres disponibles
#define LIG_SAISIE   LIG_GRILLE - 3		//pos-ligne pour la demande et saisie d'une case
#define LIG_MESSAGES LIG_GRILLE - 2		//pos-ligne pour l'affichage des autres messages


//Permet d'afficher les règles du jeu
void afficher_instructions();

//Permet d'afficher la liste des chiffres dispo (sur la ligne 0) et du score (sur la ligne 1).
//PARAM.: la liste des chiffres encore disponibles et le score à date
//RETOUR: Aucun
void afficher_infos_jeu(const t_tab_chiffres nbr_chiffres, int pts);

//Permet d'afficher la grille des chiffres.
//PARAM.: la grille des chiffres et l'indice de la dernière ligne non-vide
//RETOUR: Aucun
void afficher_grille(const t_grille_nos grille, int dern_lig);

//Permet d'afficher la suggestion de deux chiffres à choisir en BLEU pendant 5 secondes.
//PARAM.: la colonne, ligne et chiffre de la première case.
//        la colonne, ligne et chiffre de la deuxième case.
//RETOUR: Aucun
void afficher_couple(int colA, int ligA, int chA, int colB, int ligB, int chB);

//Affiche le message de demande d'une saisie de case ou commande (sur la ligne 3).
//PARAM.: le numéro de la case à saisir (soit 1 ou 2)
//RETOUR: Aucun
void demander_saisie(int no_saisie);

//Les 3 fonctions suivantes servent à afficher différents messages durant le jeu
void message(const char * mess);	  //affiche un message d'information (sur la ligne 3) 

void mess_points(int pts);		 	  //affiche le nb. de points ajoutés (sur la ligne 1)
									  //Ce message sera affiché avec un effet de clignotement

void mess_erreur(const char * mess);  //affiche un message d'erreur en ROUGE (sur la ligne 3)
									  //Ce message sera affiché avec un effet de clignotement

#endif