#include "Initialisation.h"
#include "InterfaceGraphique.h"

namespace interfaceGraphique {

	// Fonction dessinPlateau
	void dessinPlateau(mlv::window_t &fenetre, plateau_t Plateau) {

		fenetre.clear(mlv::color::lightgreen);
		for (int i = 0; i < Plateau.sizeColonne; i++) {
			for (int j = 0; j < Plateau.sizeLigne; j++) {
				if (i % 2 == j % 2) {
					fenetre.draw_filled_rectangle({j * 50, i * 50}, 50, 50, mlv::color::white);
				} else {
					fenetre.draw_filled_rectangle({j * 50, i * 50}, 50, 50, mlv::color::black);
				}

				if (Plateau.data[i][j] == 1) {
					fenetre.draw_filled_circle({j * 50 + 25, i * 50 + 25}, 20, mlv::color::red);
				}
				if (Plateau.data[i][j] == 2) {
					fenetre.draw_filled_circle({j * 50 + 25, i * 50 + 25}, 20, mlv::color::blue);
				}
				if (Plateau.data[i][j] == 3) {
					fenetre.draw_filled_circle({j * 50 + 25, i * 50 + 25}, 15, mlv::color::purple);
				}
			}
		}
		fenetre.update();
	}

}

namespace Amazones {

	/**
 * Fonction jouer qui joue un tour avec un déplacement et tirer une flèche et qui met à jour le plateau au fur et à mesure
 * @param le jeu en cours, le numéro du joueur qui joue à ce tour
 * @return le jeu mis à jour à la fin du tour
 */
	jeu_t jouer(interface_graph_t &interfaceGraph, jeu_t amazones, int nbJoueur) {
		cout << endl;
		cout << "[Au tour de ";
		if (nbJoueur == 1) cout << amazones.joueur1.name;
		if (nbJoueur == 2) cout << amazones.joueur2.name;
		cout << " de jouer]" << endl;
		cout << endl;

		affichePlateau(amazones.plateau);
		interfaceGraphique::dessinPlateau(interfaceGraph.fenetre, amazones.plateau);

		index_t pionIndex = demanderPion(amazones, nbJoueur);

		while (pionIndex.ligne == -1 and pionIndex.colonne == -1) {
			pionIndex = demanderPion(amazones, nbJoueur);
		}

		// un déplacement
		if (amazones.ReineOuCavalier == 1) amazones = deplacement(amazones, nbJoueur, pionIndex);
		if (amazones.ReineOuCavalier == 2) amazones = deplacementCavalier(amazones, nbJoueur, pionIndex);

		// on rajoute à la liste de pions possédée par le joueur le nouvel emplacement de son pion après déplacement
		if (nbJoueur == 1) amazones.joueur1.pions.push_back(pionIndex);
		if (nbJoueur == 2) amazones.joueur2.pions.push_back(pionIndex);

		affichePlateau(amazones.plateau);
		interfaceGraphique::dessinPlateau(interfaceGraph.fenetre, amazones.plateau);

		// tirer une flèche
		amazones = tirerUneFleche(amazones, pionIndex);

		return amazones;
	}

	/**
	 * Fonction qui détecte si le joueur a perdu
	 * @param un joueur et un plateau
	 * @return faux si le joueur n'a pas perdu, vrai si le joueur a perdu
	 */
	bool joueurAPerdu(joueur_t joueur, plateau_t plateau) {
		for (int i = 0; i < joueur.pions.size(); i++) {
			if (nonEncercle(joueur.pions[i], plateau) == true) {
				return false;
				// Le joueur a pas perdu
			}
		// le joueur a perdu
		return true;
	}
	}

	/**
	 * Fonction qui détecte si le joueur a perdu en mode cavalier
	 * @param un joueur et un plateau
	 * @return faux si le joueur n'a pas perdu, vrai si le joueur a perdu
	 */
	bool joueurAPerduCavalier(joueur_t joueur, plateau_t plateau) {
		for (int i = 0; i < joueur.pions.size(); i++) {
			if (nonEncercleCavalier(joueur.pions[i], plateau) == true) {
				return false;
				// Le joueur a pas perdu en mode cavalier
			}
		// le joueur a perdu en mode cavalier
		return true;
	}
	}

	/**
	 * Fonction qui vérifie si le jeu est terminé ou non.
	 * @param amazones l'objet jeu contenant les données relatives au jeu
	 * @return false si la partie est terminée, true si la partie n'est pas terminée.
	 */
	bool leJeuNestPasTermine(jeu_t amazones) {
		if (amazones.ReineOuCavalier == 1) {

		if (joueurAPerdu(amazones.joueur1, amazones.plateau)) {
			cout << endl;
			cout << "[" << amazones.joueur2.name << " a remporté la partie !]" << endl;
			return false;
		}


		if (joueurAPerdu(amazones.joueur2, amazones.plateau)) {
			cout << endl;
			cout << "[" << amazones.joueur1.name << " a remporté la partie !]" << endl;
			return false;
		}
		} else {

		if (joueurAPerduCavalier(amazones.joueur1, amazones.plateau)) {
			cout << endl;
			cout << "[" << amazones.joueur2.name << " a remporté la partie !]" << endl;
			return false;
		}


		if (joueurAPerduCavalier(amazones.joueur2, amazones.plateau)) {
			cout << endl;
			cout << "[" << amazones.joueur1.name << " a remporté la partie !]" << endl;
			return false;
		}
		}

		return true;
	}

}

int main() {
	interface_graph_t interfaceGraph;
	jeu_t amazones = initialisationDuJeu();

	interfaceGraphique::dessinPlateau(interfaceGraph.fenetre, amazones.plateau);

	// size_t est un int qui n'a que des valeurs positives (unsigned int)
	size_t nbTour = 1;

	// tant que le jeu n'est pas terminé, on continue à jouer des tours
	while (Amazones::leJeuNestPasTermine(amazones)) {
		cout << endl;
		cout << "____________________________________________________________________" << endl;
		cout << "[Tour numéro " << nbTour << "]" << endl;

		// si le tour est impair, on fait jouer le joueur 1, sinon le joueur 2.
		if (nbTour % 2 == 0) {
			amazones = Amazones::jouer(interfaceGraph, amazones, 2);
		} else {
			amazones = Amazones::jouer(interfaceGraph, amazones, 1);
		}

		nbTour++;

	}

	affichePlateau(amazones.plateau);
	return 0;
}
