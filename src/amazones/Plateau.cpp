#include "Plateau.h"

/**
 * Fonction creerPlateau
 * Crée un plateau (structure qui contient un tableau 2D et deux entiers X et Y)
 * @param x, y des entiers représentant respectivement le nombre de lignes et de colonnes du plateau
 * @return un plateau
 */
plateau_t creerPlateau(int x, int y) {

	plateau_t nouveauPlateau;

	vector<vector<int> > sortie;
	sortie = vector<vector<int> >(x);


	for (int i = 0; i < x; i++) {
		sortie[i] = vector<int>(y);
	}

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			sortie[i][j] = 0;
		}
	}

	nouveauPlateau.data = sortie;
	nouveauPlateau.sizeColonne = x;
	nouveauPlateau.sizeLigne = y;

	return nouveauPlateau;

}

/**
 * Fonction affichePlateau
 * Affiche un plateau
 */
void affichePlateau(plateau_t plateau) {
	cout << "    ";
	for (int i = 0 ; i < plateau.sizeLigne ; i++) {
		cout << nombreEnLettre(i) << " ";
	}
	cout << endl;
	cout << "   ";
	for (int i = 0 ; i < plateau.sizeLigne * 2 ; i++) {
		cout << "-";
	}
	cout << endl;
	for (int i = 0; i < plateau.sizeColonne; i++) {

		cout << i + 1 << " | ";

		for (int j = 0; j < plateau.sizeLigne; j++) {
			cout << plateau.data[i][j] << " ";
		}
		cout << " |" << endl;
	}
}

/**
 * Vérifie si l'index est dans les limites du plateau
 * @param plateau l'objet plateau_t représentant un plateau
 * @param index l'objet index_t représentant un index
 * @return un booléen indiquant si l'index est dans les limites du plateau ou non
 */
bool verifierIndexDansPlateau(plateau_t plateau, index_t index) {
	//vérifier si la ligne est correcte (dans les limites du tableau)
	if (index.ligne >= plateau.sizeColonne or index.ligne < 0) {
		return false;
	}
	//vérifier si la colonne est correcte (dans les limites du tableau)
	if (index.colonne >= plateau.sizeLigne or index.colonne < 0) {
		return false;
	}

	// la colonne et la ligne sont correctes
	return true;
}

/**
 * Vérifie si la case donnée par l'index est vide
 * @param plateau l'objet plateau_t représentant un plateau
 * @param index l'objet index_t représentant un index
 * @return un booléen spécifiant si la case est vide ou non
 */
bool verifierCaseVide(plateau_t plateau, index_t index) {

	// vérifier si l'index est dans les limites du tableau
	if (verifierIndexDansPlateau(plateau, index) == true) {

		// vérifier si la case est vide
		if (plateau.data[index.ligne][index.colonne] == 0) {
			// la case est vide
			return true;
		}
		// la case n'est pas vide
		return false;

	} else {
		// l'index n'est pas dans les limites du tableau
		return false;
	}

}
