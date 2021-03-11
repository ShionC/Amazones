#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>
#include "Position.h"
#include "Plateau.h"
using namespace std;

struct joueur_t {
	string name;
	vector<index_t> pions;
};

struct jeu_t {
	plateau_t plateau;
	joueur_t joueur1;
	joueur_t joueur2;
	int totalAmazonesParJoueur;
	int ReineOuCavalier;
};

index_t caseVersIndex(int ligne, char colonne);

index_t demanderUnePosition();

int lettreEnNombre(char lettre);

char nombreEnLettre(int nombre);

string indexVersCase(index_t index);

bool nonEncercle(index_t positionInitiale, plateau_t plateau);
bool nonEncercleCavalier(index_t positionInitiale, plateau_t plateau);

index_t demanderPion(jeu_t &amazones, int nbJoueur);

jeu_t tirerUneFleche(jeu_t amazones, index_t pionIndex);
jeu_t deplacement(jeu_t amazones, int nbJoueur, index_t &pionIndex);
jeu_t deplacementCavalier(jeu_t amazones, int nbJoueur, index_t &pionIndex);
