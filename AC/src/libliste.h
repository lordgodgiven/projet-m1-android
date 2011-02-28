#ifndef LIBLISTE_H
#define LIBLISTE_H

#include <stdlib.h>
#include <stdio.h>


typedef enum casErreur{
	ECHEC_ALLOC_PL, ECHEC_ALLOC_L, 
	ECHEC_ALLOC_PG, ECHEC_ALLOC_G,
	EXISTE, EXISTE_PAS, 
	PAS_ERREUR
} casErreur;

typedef struct TypVoisins{
	int voisin;
	int poidsVoisin;
	struct TypVoisins *voisinSuivant;
} TypVoisins;

casErreur initialisationListe(TypVoisins **liste);
casErreur ajouterDebut(TypVoisins **liste, int voisin, int poidsVoisin);
casErreur supprimerVoisin(TypVoisins **liste, int voisin);
casErreur nettoyerTout(TypVoisins **liste);
casErreur supprimerTout(TypVoisins **liste);
int tailleTypVoisins(TypVoisins *liste);
void affichageListe(TypVoisins *liste);
casErreur verifAllocationPL(TypVoisins **liste);
casErreur verifAllocationL(TypVoisins *liste);
casErreur existeVoisin(TypVoisins *liste, int voisin);
int estVide(TypVoisins *liste);

#endif //LIBLISTE_H
