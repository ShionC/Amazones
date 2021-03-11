#include "Initialisation.h"

/**
 * Initialise le nom des joueurs
 * @param amazones l'objet jeu_t contenant les données relatives au jeu
 * @return l'objet jeu_t modifié par cette fonction
 */
jeu_t initialisationNomsDesJoueurs(jeu_t amazones) {

	cout << "Veuillez renseigner le pseudo du 1er joueur : ";
	cin >> amazones.joueur1.name;

	cout << "Veuillez renseigner le pseudo du 2ème joueur : ";
	cin >> amazones.joueur2.name;
	cout << endl;

	return amazones;
}

/**
 * Initialise le plateau du jeu
 * @return l'objet plateau_t créé
 */
plateau_t initialisationPlateau() {
	cout << "________________________________________________" << endl;
	cout << "[Configuration de la taille du plateau.]" << endl;
	cout << endl;

	int x;
	int y;

	cout << "Nombre de lignes ? = ";

	cin >> x;

	if (x < 2) {
		cerr << "Veuillez entrer un nombre supérieur ou égal à 2." << endl;
		return initialisationPlateau();
	}

	cout << "Nombre de colonnes ? = ";
	cin >> y;

	if (y < 2) {
		cerr << "Veuillez entrer un nombre supérieur ou égal à 2." << endl;
		return initialisationPlateau();
	}

	cout << endl;

	plateau_t Plateau = creerPlateau(x, y);

	return Plateau;
}

/**
 * Initialise le nombre total d'amazones par joueur
 * @param amazones l'objet jeu_t contenant les données relatives au jeu
 * @return l'objet jeu_t modifié par cette fonction
 */
jeu_t initialisationNbTotalAmazones(jeu_t amazones) {

	int totalAmazonesParJoueur;

	cout << endl;
	cout << "Combien d'Amazones au total pour chaque joueur ? : ";
	cin >> totalAmazonesParJoueur;

	// si le nombre total d'amazones par joueur est inférieur ou égal à 0, c'est une erreur
	if (totalAmazonesParJoueur <= 0) {
		cerr << "Le nombre total d'Amazones est incorrect." << endl;
		return initialisationNbTotalAmazones(amazones);
	}

	if (totalAmazonesParJoueur * 2 > amazones.plateau.sizeColonne * amazones.plateau.sizeLigne) {
		cerr << "Le nombre total d'Amazones donné est trop élevé pour le plateau actuellement configuré." << endl;
		return initialisationNbTotalAmazones(amazones);
	}

	amazones.totalAmazonesParJoueur = totalAmazonesParJoueur;

	cout << endl;

	return amazones;
}

jeu_t initialisationTypeReineOuCavalier(jeu_t amazones) {
	cout << "Voulez-vous jouer en mode normal (1) ou en mode cavalier (2) ? : ";
	cin >> amazones.ReineOuCavalier;

	if (amazones.ReineOuCavalier < 1 or amazones.ReineOuCavalier > 2) {
		cerr << "Veuillez entrer soit 1 (reine) soit 2 (cavalier), merci." << endl;
		return initialisationTypeReineOuCavalier(amazones);
	}

	cout << endl;
	return amazones;
}

/**
 * Essaye de poser un pion pour un joueur sur le plateau contenu dans la structure jeu_t
 * @param amazones l'objet jeu_t contenant les données relatives au jeu
 * @param nbJoueur le numéro du joueur, 1 ou 2 si il n'y a que deux joueurs
 * @return un booléen, indiquant si la pose du pion a échoué ou non
 */
bool poserPion(jeu_t &amazones, int nbJoueur, index_t Index) {

	//vérifier si l'emplacement n'est pas déjà occupé par une amazones
	if (verifierCaseVide(amazones.plateau, Index) == true) {
		amazones.plateau.data[Index.ligne][Index.colonne] = nbJoueur;

		// en fonction du joueur (1 ou 2), on lui ajoute à sa liste personnelle de pions
		// l'index du nouveau pion posé
		if (nbJoueur == 1) amazones.joueur1.pions.push_back(Index);
		if (nbJoueur == 2) amazones.joueur2.pions.push_back(Index);

		affichePlateau(amazones.plateau);
		cout << endl;
		return true;
	} else {
		cout << "Case occupée. Recommencer." << endl;
		return false;
	}
}

/**
 * Initialise les pions pour un joueur dans le jeu.
 * @param amazones l'objet jeu contenant les données relatives au jeu
 * @param nbJoueur le numéro du joueur, 1 ou 2 si il n'y a que deux joueurs
 * @return l'objet jeu_t modifié par cette fonction
 */
jeu_t initialisationPions(jeu_t amazones, int nbJoueur) {

	cout << "____________________________________________________________________" << endl;

	string nomJoueur;

	if (nbJoueur == 1) nomJoueur = amazones.joueur1.name;
	if (nbJoueur == 2) nomJoueur = amazones.joueur2.name;

	cout << "[Placement des Amazones pour " << nomJoueur << "]" << endl;
	cout << endl;

	// essaye de poser tous les pions pour un seul joueur
	for (int i = 1; i <= amazones.totalAmazonesParJoueur; i++) {
		// tant que la pose du pion est erronée, recommencer

		index_t index = demanderUnePosition();

		while (poserPion(amazones, nbJoueur, index) == false);
	}
	return amazones;
}

/**
 * Lance l'initialisation du jeu
 * @return le jeu après l'initialisation
 */
jeu_t initialisationDuJeu() {
	cout << endl;
	cout << "[Bienvenue dans le jeu Amazones]" << endl;
	cout << endl;

	jeu_t amazones;
	joueur_t joueur1;
	joueur_t joueur2;

	amazones.joueur1 = joueur1;
	amazones.joueur2 = joueur2;
	amazones = initialisationNomsDesJoueurs(amazones);

	amazones.plateau = initialisationPlateau();

	affichePlateau(amazones.plateau);

	amazones = initialisationNbTotalAmazones(amazones);
	amazones = initialisationTypeReineOuCavalier(amazones);

	cout << endl;

	cout << "____________________________________________________________________" << endl;
	cout << "[Configuration de l'emplacement des pions de base]" << endl;

	// Initialisation des pions pour le joueur 1
	amazones = initialisationPions(amazones, 1);
	// Initialisation des pions pour le joueur 2
	amazones = initialisationPions(amazones, 2);

	cout << "____________________________________________________________________" << endl;
	cout << "[Etat du plateau initial]" << endl;
	cout << endl;

	affichePlateau(amazones.plateau);
	return amazones;
}
