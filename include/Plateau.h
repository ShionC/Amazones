#ifndef AMAZONES_PLATEAU_H
#define AMAZONES_PLATEAU_H

#include <vector>
#include <iostream>

using namespace std;

char nombreEnLettre(int nombre);

// Fonction creer_plateau
// Structure du plateau (nombre de lignes / colonnes peut être demandé aux joueurs mais limite de 26 colonnes de A à Z)
// Création de structure plateau

struct plateau_t {
	int sizeColonne;
	int sizeLigne;
	vector<vector<int> > data;
};

// Fonction caseVersIndex: Nom des lignes / colonnes
// (Lignes avec des chiffres, colonnes avec des lettres)
// Création de structure index

struct index_t {
	int ligne;
	int colonne;
};

void affichePlateau(plateau_t plateau);
plateau_t creerPlateau(int x, int y);
bool verifierIndexDansPlateau(plateau_t plateau, index_t index);
bool verifierCaseVide(plateau_t plateau, index_t index);

#endif //AMAZONES_PLATEAU_H
