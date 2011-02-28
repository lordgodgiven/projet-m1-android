#include "libgraphe.h"

/* initialise le graphe avec nbSommets maximum*/
casErreur initialisationGraphe(TypGraphe **graphe, int nbSommets){
	(*graphe) = (TypGraphe*) malloc(sizeof(TypGraphe));

	casErreur erreur = verifAllocationPG(graphe);
	if(erreur != PAS_ERREUR)
		//printf("Probleme allocation memoire pour le graphe\n");
		return erreur;

	(*graphe)->nbMaxSommets = nbSommets;
	(*graphe)->listesAdjencences = 
		(TypVoisins**) malloc(nbSommets * sizeof(TypVoisins*));

	erreur = verifAllocationPL((*graphe)->listesAdjencences);
//	if((*graphe)->listesAdjencences == NULL){
//		printf("Probleme allocation memoire pour le graphe\n");
	if(erreur != PAS_ERREUR)
		return erreur;

	int i;
	for(i=0; i<nbSommets; i++)
		(*graphe)->listesAdjencences[i] = NULL;
	
	return 0;
}

/* ins�re le sommet dans le graphe : initialisation de sa liste */
casErreur insertionSommet(TypGraphe **graphe, int sommet){
	casErreur erreur = verifAllocationPG(graphe);
	if(erreur != PAS_ERREUR)
		return erreur;

	if(sommet - 1 > (*graphe)->nbMaxSommets && sommet - 1 < 0)
//		printf("Erreur dans l'insertion du sommet : %d\n", sommet);
//		printf("Sommet incorrect, d�passement de taille\n");
		return INSERT_SOMMET_INCORRECT;

	initialisationListe(&((*graphe)->listesAdjencences[sommet-1]));
//	ajouterDebut(&((*graphe)->listesAdjencences[sommet-1]), 5, 2);
//	affichageListe((*graphe)->listesAdjencences[sommet-1]);

	return PAS_ERREUR;
}

/* ins�re une ar�te entre deux sommets avec son poids */
/* fonction utile pour l'ajout manuel */
casErreur insertionArete(TypGraphe **graphe, int sommetDebut, 
		int sommetSuivant, int poids){
	casErreur erreur = verifAllocationPG(graphe);
	if(erreur != PAS_ERREUR)
		return erreur;

	int nbMaxSommets = (*graphe)->nbMaxSommets;
	if((sommetDebut-1 > nbMaxSommets) || (sommetSuivant-1 > nbMaxSommets) ||
			sommetDebut-1 < 0 || sommetSuivant-1 < 0)
//		printf("Erreur dans l'insertion d'une arete entre %d et %d\n", 
//			sommetDebut, sommetSuivant);
//		printf("Un des sommets est incorrect, d�passement de taille\n");
		return INSERT_ARETE_SOMMET_INCORRECT;

	if((*graphe)->listesAdjencences[sommetDebut - 1] == NULL ||
		(*graphe)->listesAdjencences[sommetSuivant - 1] == NULL)
//		printf("Erreur dans l'insertion d'une arete entre %d et %d\n", 
//			sommetDebut, sommetSuivant);
//		printf("Un des sommets n'a pas �t� ajout�\n");
		return INSERT_ARETE_SOMMET_EXISTE_PAS;

	ajouterDebut(&((*graphe)->listesAdjencences[sommetDebut-1]), 
		sommetSuivant-1, poids);

	return 0;
}

/* supprime le sommet et tous les autres sommets qui ont une 
ar�te en commun avec lui */
int suppressionSommet(TypGraphe **graphe, int sommet){
	if(verifAllocationPG(graphe) < 0)
		return -1;
	
	if(sommet - 1 > (*graphe)->nbMaxSommets){
		printf("Erreur dans la suppression du sommet : %d\n", sommet);
		printf("Sommet incorrect, d�passement de taille\n");
		return -1;
	}

	supprimerTout(&((*graphe)->listesAdjencences[sommet-1]));

	int i;
	for(i=0; i<(*graphe)->nbMaxSommets; i++){
		if((*graphe)->listesAdjencences[i] != NULL)
			supprimerVoisin(&((*graphe)->listesAdjencences[i]), sommet-1);
	}

	return 0;
}

int suppressionArete(TypGraphe **graphe, int sommetDebut, int sommetSuivant){
	if(verifAllocationPG(graphe) < 0)
		return -1;
	
	if((sommetDebut - 1 > (*graphe)->nbMaxSommets) || 
			(sommetSuivant - 1 > (*graphe)->nbMaxSommets)){
		printf("Erreur dans la suppression d'une arete entre %d et %d\n",
			sommetDebut, sommetSuivant);
		printf("Sommet incorrect, d�passement de taille\n");
		return -1;
	}

	supprimerVoisin(&((*graphe)->listesAdjencences[sommetDebut-1]), 
		sommetSuivant-1);

	return 0;
}

/* v�rifie qu'un pointeur sur graphe est bien initialis� */
int verifAllocationPG(TypGraphe **graphe){	
	if(*graphe == NULL || graphe == NULL){
		printf("Pointeur sur graphe non alloue\n");
		return -1;
	}

	return 0;
}

/* v�rifie qu'une graphe est bien initialis�e */
int verifAllocationG(TypGraphe *graphe){
	if(graphe == NULL){
		printf("Graphe non alloue\n");
		return -1;
	}

	return 0;
}

void affichageGraphe(TypGraphe *graphe){
	if(verifAllocationG(graphe) < 0)
		return;

	int i;
	TypVoisins *liste;
	for(i=0; i<graphe->nbMaxSommets; i++){
		liste = graphe->listesAdjencences[i];
		if(estVide(liste) > 0){
			printf("Sommet entr� : %d\n", i+1);
			while(liste->voisin != -1){
				printf("\t\tVers %d avec le poids %d\n", (liste->voisin)+1, liste->poidsVoisin);
				liste = liste->voisinSuivant;
			}
		}
	}

	return;
}

int supprimerGraphe(TypGraphe **graphe){
	if(verifAllocationPG(graphe) < 0)
		return -1;

	int i;
	for(i=0; i<(*graphe)->nbMaxSommets; i++){
		supprimerTout(&((*graphe)->listesAdjencences[i]));
	}

	(*graphe) = NULL;
	return 0;
}

int nombreMaxSommetsGraphe(TypGraphe *graphe){
	if(verifAllocationG(graphe) < 0)
		return -1;

	return graphe->nbMaxSommets;
}