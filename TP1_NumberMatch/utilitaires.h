/*
Module: utilitaires.h   (*** MODULE DONNÉ AUX ÉLÈVES ***)

Description: Module de fonctions utilitaires : 
             Offre une fonction de génération d'un réel aléatoire entre un "min" et "max".
             Offre une fonction de génération d'un entier aléatoire entre un "min" et "max".
             
Auteur: Anis Boubaker et Eric Thé
*/

#ifndef UTILITAIRES_H
#define UTILITAIRES_H

/*
Fonction: init_rand
Description: Initialise le générateur aléatoire "rand()" selon l'heure de l'ordi.
             Cette fonction doit être appellée une fois avant d'uiliser "rand()".

Paramètres: aucun
Retour: aucun
*/
void init_rand(void);

/*
Fonction: reel_aleatoire
Description: Fonction qui retourne un réel aléatoire entre min et max.

Paramètres:
        min (réel): borne minimale de l'intervale du nombre aléatoire
        max (réel): borne maximale de l'intervale du nombre aléatoire
Retour: (réel) nombre aléatoire entre min et max.
Spécifications: on présume que la fonction "init_rand()" à été appellée une fois
                avant d'utiliser cette fonction.
*/
double reel_aleatoire(double min, double max);

/*
Fonction: entier_aleatoire
Description: Fonction qui retourne un entier aléatoire entre min et max.

Paramètres:
        min (entier): borne minimale de l'intervale du nombre aléatoire
        max (entier): borne maximale de l'intervale du nombre aléatoire
Retour: (entier) nombre aléatoire entre min et max.
Spécifications: on présume que la fonction "init_rand()" à été appellée une fois
                avant d'utiliser cette fonction.
*/
int entier_aleatoire(int min, int max);

#endif   //#if !UTILITAIRES_H