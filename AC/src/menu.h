#ifndef MENU_H
#define MENU_H

#include "libgraphe.h"
#include <string.h>

typedef enum {
	CREATION = 1,
	LECTURE_EXISTANT = 2,
	INSERT_SOMMET = 3,
	INSERT_ARETE = 4,
	SUPPRIME_SOMMET = 5,
	SUPPRIME_ARETE = 6,
	AFFICHAGE = 7,
	SAUVEGARDE = 8,
	QUITTER = 9
} Menu;

void clearScanf(void);
void menu(TypGraphe** grapheCourant);
void afficherMenu(TypGraphe** grapheCourant);
void actionsMenu(TypGraphe** grapheCourant);
int demandeSuppression(TypGraphe** grapheCourant);
void afficherErreur(casErreur erreur);
void creationGraphe(TypGraphe** grapheCourant);
void lectureFichierExistant(TypGraphe** grapheCourant);
void insertionSommetGraphe(TypGraphe** grapheCourant);	
void insertionAreteGraphe(TypGraphe** grapheCourant);
void supprimeSommetGraphe(TypGraphe** grapheCourant);
void supprimeAreteGraphe(TypGraphe** grapheCourant);
void sauvegardeGraphe(TypGraphe** grapheCourant);
void quitterMenuGraphe(TypGraphe** grapheCourant);

#endif //MENU_H
