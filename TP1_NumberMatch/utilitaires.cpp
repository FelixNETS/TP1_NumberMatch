/*
Titre: utilitaires.cpp    (*** MODULE DONNÉ AUX ÉLÈVES ***)
Description: Fonctions du module d'utilitaires, comprenant des fonctions diverses
			 de génération de nombre aléatoires.
Auteur: Anis Boubaker et Eric Thé
*/

/************ COMMANDES DE PRÉPROCESSEUR **************/
#include <stdlib.h>
#include <time.h>
#include "utilitaires.h"

/********* IMPLÉMENTATIONS DES FONCTIONS **************/

/*---------------------- init_rand() -------------------------------*/
//initialise le générateur aléatoire "rand()" selon l'heure de l'ordi.
void init_rand(void)
{
	srand((unsigned int)time(NULL));	//exécuter le "seed-rand" (init.)
	rand();								//un premier appel pour sauter le premier nombre alea.
}

/*--------------------- reel_aleatoire() ------------------------------*/
/* Fonction aléatoire qui renvoie un réel inclu entre [min..max]. */
double reel_aleatoire(double min, double max)
{
	/*	Posons que x vaut rand() / (RAND_MAX + 0.0000001), alors
		x                              E  [0, 1[
		x * (max - min)                E  [0, max - min
		min + x * (max - min)          E  [min, max[
	*/
	return (min + rand() / (RAND_MAX + 0.0000001) * (max - min));
}

/*--------------------- entier_aleatoire() ------------------------------*/
/* Fonction aléatoire qui renvoie un entier inclu entre [min..max]. */
int entier_aleatoire(int min, int max) {
	return (int)((1.0 * rand()) / (RAND_MAX + 1) * (max - min + 1)) + min;
}