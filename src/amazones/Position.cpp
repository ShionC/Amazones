#include "Position.h"

// Emplacements de la reine

/**
 * Calcule les emplacements où un pion est possible de se déplacer en diagonale
 * @param un index avec la position initiale du pion
 * @param un plateau
 * @return un tableau d'index avec les index des cases où on peut se déplacer
 */
vector<index_t> calculerPositionsDiagonales(index_t positionInitiale, plateau_t plateau) {
	vector<index_t> positions;

	// regarder en haut à gauche
	int ligne = positionInitiale.ligne - 1;
	int colonne = positionInitiale.colonne - 1;

	while (ligne >= 0 and colonne >= 0) {
		index_t pos = positionInitiale;

		pos.colonne = colonne;
		pos.ligne = ligne;

		if (verifierCaseVide(plateau, pos)) {
			positions.push_back(pos);
		} else {
			// Si on tombe sur une case non vide, on arrête de calculer des positions possibles
			break;
		}

		colonne--;
		ligne--;
	}

	// regarder en haut à droite
	ligne = positionInitiale.ligne - 1;
	colonne = positionInitiale.colonne + 1;

	while (ligne >= 0 and colonne < plateau.sizeLigne) {
		index_t pos = positionInitiale;

		pos.colonne = colonne;
		pos.ligne = ligne;

		if (verifierCaseVide(plateau, pos)) {
			positions.push_back(pos);
		} else {
			// Si on tombe sur une case non vide, on arrête de calculer des positions possibles
			break;
		}

		colonne++;
		ligne--;
	}

	// regarder en bas à gauche
	ligne = positionInitiale.ligne + 1;
	colonne = positionInitiale.colonne - 1;

	while (ligne < plateau.sizeColonne and colonne >= 0) {
		index_t pos = positionInitiale;

		pos.colonne = colonne;
		pos.ligne = ligne;

		if (verifierCaseVide(plateau, pos)) {
			positions.push_back(pos);
		} else {
			// Si on tombe sur une case non vide, on arrête de calculer des positions possibles
			break;
		}

		colonne--;
		ligne++;
	}

	// regarder en bas à droite
	ligne = positionInitiale.ligne + 1;
	colonne = positionInitiale.colonne + 1;

	while (ligne < plateau.sizeColonne and colonne < plateau.sizeLigne) {
		index_t pos = positionInitiale;

		pos.colonne = colonne;
		pos.ligne = ligne;

		if (verifierCaseVide(plateau, pos)) {
			positions.push_back(pos);
		} else {
			// Si on tombe sur une case non vide, on arrête de calculer des positions possibles
			break;
		}

		colonne++;
		ligne++;
	}

	return positions;
}

/**
 * Calcule les emplacements où un pion est possible de se déplacer en ligne droite
 * @param un index avec la position initiale du pion
 * @param un plateau
 * @return un tableau d'index avec les index des cases où on peut se déplacer
 */
vector<index_t> calculerPositionsOrthogonales(index_t positionInitiale, plateau_t plateau) {
	vector<index_t> positions;

	// regarder à droite horizontalement
	for (int colonne = positionInitiale.colonne + 1; colonne < plateau.sizeLigne; colonne++) {

		index_t pos = positionInitiale;

		pos.colonne = colonne;

		if (verifierCaseVide(plateau, pos)) {
			positions.push_back(pos);
		} else {
			// Si on tombe sur une case non vide, on arrête de calculer des positions possibles
			break;
		}

	}

	// regarder à gauche horizontalement
	for (int colonne = positionInitiale.colonne - 1; colonne >= 0; colonne--) {

		index_t pos = positionInitiale;

		pos.colonne = colonne;

		if (verifierCaseVide(plateau, pos)) {
			positions.push_back(pos);
		} else {
			// Si on tombe sur une case non vide, on arrête de calculer des positions possibles
			break;
		}

	}

	// regarder en bas verticalement
	for (int ligne = positionInitiale.ligne + 1; ligne < plateau.sizeColonne; ligne++) {
		index_t pos = positionInitiale;

		pos.ligne = ligne;

		if (verifierCaseVide(plateau, pos)) {
			positions.push_back(pos);
		} else {
			// Si on tombe sur une case non vide, on arrête de calculer des positions possibles
			break;
		}
	}

	// regarder en haut verticalement
	for (int ligne = positionInitiale.ligne - 1; ligne >= 0; ligne--) {
		index_t pos = positionInitiale;

		pos.ligne = ligne;

		if (verifierCaseVide(plateau, pos)) {
			positions.push_back(pos);
		} else {
			// Si on tombe sur une case non vide, on arrête de calculer des positions possibles
			break;
		}
	}

	return positions;
}

// Emplacement du cavalier
/** Calcule les emplacements où un pion est possible de se déplacer en mode cavalier
 * @param un index avec la position initiale du pion
 * @param un plateau
 * @return un tableau d'index avec les index des cases où on peut se déplacer
 */
vector<index_t> calculerPositionsCheval(index_t positionInitiale, plateau_t plateau) {
	vector<index_t> positions;

	// vérifier les deux positions à gauches
	index_t pos = positionInitiale;

	pos.colonne -= 2;
	pos.ligne += 1;

	if (verifierCaseVide(plateau, pos)) {
		positions.push_back(pos);
	}
	pos.ligne -= 2;
	if (verifierCaseVide(plateau, pos)) {
		positions.push_back(pos);
	}

	// vérifier les deux positions à droite
	pos = positionInitiale;

	pos.colonne += 2;
	pos.ligne += 1;

	if (verifierCaseVide(plateau, pos)) {
		positions.push_back(pos);
	}
	pos.ligne -= 2;
	if (verifierCaseVide(plateau, pos)) {
		positions.push_back(pos);
	}

	// vérifier les deux positions en bas
	pos = positionInitiale;

	pos.colonne += 1;
	pos.ligne += 2;

	if (verifierCaseVide(plateau, pos)) {
		positions.push_back(pos);
	}
	pos.colonne -= 2;
	if (verifierCaseVide(plateau, pos)) {
		positions.push_back(pos);
	}

	// vérifier les deux positions en haut
	pos = positionInitiale;

	pos.colonne += 1;
	pos.ligne -= 2;

	if (verifierCaseVide(plateau, pos)) {
		positions.push_back(pos);
	}
	pos.colonne -= 2;
	if (verifierCaseVide(plateau, pos)) {
		positions.push_back(pos);
	}

	return positions;
}
