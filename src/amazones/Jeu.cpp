#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>
#include "Jeu.h"

using namespace std;

#include <fstream>

// Fonction lettreEnNombre
// Convertis un encodage de type "1a" en case correspondante du tableau
int lettreEnNombre(char lettre) {
	return lettre - 'a';
}

// Fonction nombreEnLettre
// Convertis une case du tableau en encodage de type "1a"
char nombreEnLettre(int nombre) {
	return (char) (nombre + 'a');
}

/**
 * Trouve le bon index en fonction d'une ligne et d'une colonne données en paramètre
 * @param ligne
 * @param colonne
 * @return un objet index_t représentant un index
 */
index_t caseVersIndex(int ligne, char colonne) {

	index_t nouvelIndex;

	nouvelIndex.ligne = ligne - 1; // trouve la bonne ligne
	nouvelIndex.colonne = lettreEnNombre(colonne); // trouve la bonne colonne

	return nouvelIndex;
}

/**
 * Vérifie si un pion peut encore se déplacer
 * @param l'index de la position initiale du pion
 * @param un plateau
 * @return vrai si le pion est encore libre, faux si le pion est encerclé
 */
bool nonEncercle(index_t positionInitiale, plateau_t plateau) {

	vector<index_t> positions;
	positions = vector<index_t>(8);
	positions[0].ligne = positionInitiale.ligne - 1;
	positions[0].colonne = positionInitiale.colonne - 1;
	positions[1].ligne = positionInitiale.ligne - 1;
	positions[1].colonne = positionInitiale.colonne;
	positions[2].ligne = positionInitiale.ligne - 1;
	positions[2].colonne = positionInitiale.colonne + 1;
	positions[3].ligne = positionInitiale.ligne;
	positions[3].colonne = positionInitiale.colonne - 1;
	positions[4].ligne = positionInitiale.ligne;
	positions[4].colonne = positionInitiale.colonne + 1;
	positions[5].ligne = positionInitiale.ligne + 1;
	positions[5].colonne = positionInitiale.colonne - 1;
	positions[6].ligne = positionInitiale.ligne + 1;
	positions[6].colonne = positionInitiale.colonne;
	positions[7].ligne = positionInitiale.ligne + 1;
	positions[7].colonne = positionInitiale.colonne + 1;

	for (int i = 0; i < positions.size(); i++) {
		if (verifierCaseVide(plateau, positions[i])) {
// Il y a au moins une case vide autour de la position initiale
			return true;
		}
	}
// Toutes les cases sont occupées autour de la position initiale
	return false;
}

/**
 * Vérifie si un pion peut encore se déplacer en mode cavalier
 * @param l'index de la position initiale du pion
 * @param un plateau
 * @return vrai si le pion est encore libre, faux si le pion est encerclé
 */
bool nonEncercleCavalier(index_t positionInitiale, plateau_t plateau) {

	vector<index_t> positions;
	positions = vector<index_t>(8);
	positions[0].ligne = positionInitiale.ligne - 1;
	positions[0].colonne = positionInitiale.colonne - 2;
	positions[1].ligne = positionInitiale.ligne - 2;
	positions[1].colonne = positionInitiale.colonne - 1;
	positions[2].ligne = positionInitiale.ligne - 1;
	positions[2].colonne = positionInitiale.colonne + 2;
	positions[3].ligne = positionInitiale.ligne - 2;
	positions[3].colonne = positionInitiale.colonne + 1;
	positions[4].ligne = positionInitiale.ligne + 1;
	positions[4].colonne = positionInitiale.colonne - 2;
	positions[5].ligne = positionInitiale.ligne + 2;
	positions[5].colonne = positionInitiale.colonne - 1;
	positions[6].ligne = positionInitiale.ligne + 1;
	positions[6].colonne = positionInitiale.colonne + 2;
	positions[7].ligne = positionInitiale.ligne + 2;
	positions[7].colonne = positionInitiale.colonne + 1;

	for (int i = 0; i < positions.size(); i++) {
		if (verifierCaseVide(plateau, positions[i])) {
// Il y a au moins une case vide où le joueur peut se déplacer en mode cavalier
			return true;
		}
	}
// Toutes les cases cavalier sont occupées autour de la position initiale
	return false;
}

/**
 * Trouve le bon index en fonction d'une ligne et d'une colonne données en paramètre
 * @param un objet index_t représentant un index
 * @return la position de la case dans le tableau en chaine de caractères
 */
string indexVersCase(index_t index) {
	string casePos = to_string(index.ligne + 1);

	casePos.push_back(nombreEnLettre(index.colonne));

	return casePos;
}

/**
 * Fonction qui ajoute deux tableaux dans un meme tableau
 * @param deux tableaux
 * @return un tableau avec les valeurs des deux tableaux
 */
template<typename T>
vector<T> fusionTableaux(vector<T> t1, vector<T> t2) {

	vector<T> t = vector<T>(t1.size() + t2.size());

	for (int i = 0; i < t1.size(); i++) {
		t[i] = t1[i];
	}
	for (int i = t1.size(); i < t.size(); i++) {
		t[i] = t2[i - t1.size()];
	}
	return t;
}

/**
 * Fonction qui demande au joueur la liste des Amazones qu'il possède et lui demande de choisir l'un d'entre eux
 * @param le jeu amazone en cours, un entier correspondant au numéro du joueur qui joue à ce tour
 * @return index du pion que le joueur a choisi
 */
index_t demanderPion(jeu_t &amazones, int nbJoueur) {

	joueur_t joueur;
	index_t indexDerreur = {-1, -1};

	if (nbJoueur == 1) {
		joueur = amazones.joueur1;
	} else if (nbJoueur == 2) {
		joueur = amazones.joueur2;
	} else {
		// si le numéro du joueur est inférieur à 1 ou supérieur à 2, nous sommes en cas d'erreur,
		// car il n'y a que 2 joueurs possibles.

		cerr << "Le nombre de joueur est incorrect." << endl;

		return indexDerreur;
	}

	// si le joueur n'a pas de pion, c'est une erreur.
	if (joueur.pions.empty()) {
		cerr << "Vous n'avez aucun pion." << endl;

		return indexDerreur;
	}

	cout << endl;
	cout << "Liste des Amazones que vous possédez et leur emplacement :" << endl << endl;

	// affiche tous les pions que le joueur possède
	for (int i = 0; i < joueur.pions.size(); i++) {
	if (amazones.ReineOuCavalier == 1) {
		if (nonEncercle(joueur.pions[i], amazones.plateau)) {
		cout << i + 1 << ": " << indexVersCase(joueur.pions[i]) << endl;
		// exemple d'affichage -> "1: 1a"
		}
	} else {
		if (nonEncercleCavalier(joueur.pions[i], amazones.plateau)) {
		cout << i + 1 << ": " << indexVersCase(joueur.pions[i]) << endl;
		}
	}
	}
	cout << endl;
	cout << joueur.name << ", choisissez un de vos pions en entrant un nombre inférieur ou égal à " << joueur.pions.size()
		 << " : ";
	// size_t est un int qui n'a que des valeurs positives
	size_t choix;
	cin >> choix;

	// si le joueur fait un choix qu'il ne peut pas faire, c'est une erreur.
	if (choix < 1 or choix > joueur.pions.size()) {
		cerr << "Ce pion choisi est inexistant." << endl;

		return indexDerreur;
	}

	// supprime l'élément du tableau que le joueur a choisi
	// amazones.joueur1.pions.begin() est l'itérateur correspondant au début du tableau <=> amazones.joueur1.pions[0]
	if (nbJoueur == 1) amazones.joueur1.pions.erase(amazones.joueur1.pions.begin() + (choix - 1));
	if (nbJoueur == 2) amazones.joueur2.pions.erase(amazones.joueur2.pions.begin() + (choix - 1));

	return joueur.pions[choix - 1];
}

/**
 * Fonction qui demande directement au joueur de sélectionner un emplacement
 * @return l'index de la case choisie
 */
index_t demanderUnePosition() {
	int ligne;
	char colonne;

	cout << "Entrez le numéro de la ligne : ";
	cin >> ligne;

	cout << "Entrez la lettre en minuscule de la colonne : ";
	cin >> colonne;
	cout << endl;

	return caseVersIndex(ligne, colonne);
}

/**
 * Fonction qui propose des positions possibles et qui récupère le choix du joueur
 * @param un tableau d'index correspondant aux positions possibles
 * @return un index correspondant à la position choisie
 */
index_t proposerPositionsEtRecupererReponse(vector<index_t> positionsPossibles) {

	int i = 0;

	index_t indexDerreur = {-1, -1};

	if (positionsPossibles.empty()) {
		cerr << "Il n'y a pas de position possibles." << endl;
		return indexDerreur;
	}

	for (index_t index : positionsPossibles) {
		cout << i + 1 << ": " << indexVersCase(index) << endl;
		i++;
	}
	cout << endl;
	cout << "Veuillez choisir un emplacement en entrant un nombre inférieur ou égal à " << positionsPossibles.size()
		 << " : ";

	int choix;
	cout << endl;
	cin >> choix;

	// si le choix n'est pas dans les limites du possible, c'est une erreur
	if (choix < 1 or choix > positionsPossibles.size()) {
		cerr << "Choix incorrect" << endl;
		return indexDerreur;
	}

	return positionsPossibles[choix - 1];
}

/**
 * Fonction qui donne au joueur les emplacements possibles de déplacement et qui déplace le pion
 * @param le jeu en cours, le numéro du joueur qui joue le tour et l'index du pion à déplacer
 * @return le jeu mis à jour avec le déplacement
 */
jeu_t deplacement(jeu_t amazones, int nbJoueur, index_t &pionIndex) {

	vector<index_t> positionsOrthogonales = calculerPositionsOrthogonales(pionIndex, amazones.plateau);
	vector<index_t> positionsDiagonales = calculerPositionsDiagonales(pionIndex, amazones.plateau);

	vector<index_t> positionsPossibles = fusionTableaux(positionsDiagonales, positionsOrthogonales);

	if (positionsPossibles.empty()) {
		cout << "Aucun déplacement n'est possible pour ce pion." << endl;
		return amazones;
	}

	cout << endl;
	cout << "Votre Amazone peut aller sur les cases suivantes :" << endl << endl;

	index_t positionChoisie = proposerPositionsEtRecupererReponse(positionsPossibles);

	// gérer les cas d'erreur
	while (positionChoisie.colonne == -1 and positionChoisie.ligne == -1) {
		positionChoisie = proposerPositionsEtRecupererReponse(positionsPossibles);
	}

	// déplacement du joueur, mise à jour du plateau
	amazones.plateau.data[pionIndex.ligne][pionIndex.colonne] = 0;
	amazones.plateau.data[positionChoisie.ligne][positionChoisie.colonne] = nbJoueur;

	// mise à jour de la position du pion choisit
	pionIndex.colonne = positionChoisie.colonne;
	pionIndex.ligne = positionChoisie.ligne;

	return amazones;
}

/**
 * Fonction qui donne au joueur les emplacements possibles de déplacement en mode cavalier et qui déplace le pion
 * @param le jeu en cours, le numéro du joueur qui joue le tour et l'index du pion à déplacer
 * @return le jeu mis à jour avec le déplacement
 */
jeu_t deplacementCavalier(jeu_t amazones, int nbJoueur, index_t &pionIndex) {

	vector<index_t> positionsCheval = calculerPositionsCheval(pionIndex, amazones.plateau);

	if (positionsCheval.empty()) {
		cout << "Aucun déplacement n'est possible pour ce pion." << endl;
		return amazones;
	}

	cout << endl;
	cout << "Votre Amazone peut aller sur les cases suivantes :" << endl << endl;

	index_t positionChoisie = proposerPositionsEtRecupererReponse(positionsCheval);

	// gérer les cas d'erreur
	while (positionChoisie.colonne == -1 and positionChoisie.ligne == -1) {
		positionChoisie = proposerPositionsEtRecupererReponse(positionsCheval);
	}

	// déplacement du joueur, mise à jour du plateau
	amazones.plateau.data[pionIndex.ligne][pionIndex.colonne] = 0;
	amazones.plateau.data[positionChoisie.ligne][positionChoisie.colonne] = nbJoueur;

	// mise à jour de la position du pion choisit
	pionIndex.colonne = positionChoisie.colonne;
	pionIndex.ligne = positionChoisie.ligne;

	return amazones;
}

/**
 * Fonction qui tire une flèche
 * @param le jeu en cours, l'index d'un pion
 * @return le jeu mis à jour avec le lancé de la flèche
 */
jeu_t tirerUneFleche(jeu_t amazones, index_t pionIndex) {

	vector<index_t> positionsOrthogonales = calculerPositionsOrthogonales(pionIndex, amazones.plateau);
	vector<index_t> positionsDiagonales = calculerPositionsDiagonales(pionIndex, amazones.plateau);

	vector<index_t> positionsPossibles = fusionTableaux(positionsDiagonales, positionsOrthogonales);
	cout << endl;
	cout << "Liste des emplacements où vous pouvez envoyer une flèche :" << endl << endl;

	index_t positionChoisie = proposerPositionsEtRecupererReponse(positionsPossibles);

	if (positionChoisie.ligne == -1 and positionChoisie.colonne == -1) {
		cerr << "Vous ne pouvez pas envoyer de flèche." << endl;
		return amazones;
	}

	amazones.plateau.data[positionChoisie.ligne][positionChoisie.colonne] = 3;

	return amazones;
}
