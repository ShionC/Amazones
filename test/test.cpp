#include <cassert>
#include "Plateau.h"
#include "Initialisation.h"
#include "Position.h"

// TESTS AVEC ASSERT

// Les tests ont été créé pour les fonctions qui ne prennent pas en paramètre des structures créées personnellement avec trop d'éléments intégrés ou qui ne demandent pas quelque chose directement à l'utilisateur.
// Sinon, trop long de faire des ASSERT en créant plusieurs exemples. Ces dites fonctions ont été testées au fur et à mesure de la création du jeu avec les débogages.
// Seules les fonctions jugées intéressantes à tester avec ASSERT ont été testées séparemment dans ce fichier.

// Tests des fonctions de Plateau.cpp
void verifierIndexDansPlateau_test(plateau_t plateau_ex, index_t index1_ex, index_t index2_ex, index_t index3_ex) {
	assert(verifierIndexDansPlateau(plateau_ex, index2_ex));
	assert(!verifierIndexDansPlateau(plateau_ex, index3_ex));
}

void verifierCaseVide_test(plateau_t plateau_ex, index_t index1_ex, index_t index2_ex, index_t index3_ex) {
	assert(!verifierCaseVide(plateau_ex, index1_ex));
	assert(verifierCaseVide(plateau_ex, index2_ex));
	assert(!verifierCaseVide(plateau_ex, index3_ex));
}

// Tests des fonctions de Initialisation.cpp
// Aucune fonction ne rentre dans le critère de sélection de test ASSERT développé ci-dessus (elles ont été testées au fur et à mesure)

// Tests des fonctions de Position.cpp
// Aucune fonction ne rentre dans le critère de sélection de test ASSERT développé ci-dessus (elles ont été testées au fur et à mesure)

// Tests des fonctions de Jeu.cpp
void FonctionsDeConversions_test() {
	assert(lettreEnNombre('a') == 0);
	assert(lettreEnNombre('b') == 1);
	assert(lettreEnNombre('c') == 2);
	assert(lettreEnNombre('d') == 3);

	assert(nombreEnLettre(0) == 'a');
	assert(nombreEnLettre(1) == 'b');
	assert(nombreEnLettre(2) == 'c');
	assert(nombreEnLettre(3) == 'd');

	index_t index = caseVersIndex(1, 'a');

	assert(index.colonne == 0);
	assert(index.ligne == 0);

	string casePos = indexVersCase(index);

	assert(casePos == "1a");
}

void nonEncercle_test(plateau_t plateau_ex, index_t index2_ex, index_t index4_ex) {
	assert(nonEncercle(index2_ex, plateau_ex));
	assert(!nonEncercle(index4_ex, plateau_ex));
}

int main() {

	plateau_t plateau_ex = {
			.sizeColonne = 5,
			.sizeLigne = 3,
			.data = {
					{1, 0, 0, 1, 0},
					{0, 0, 2, 3, 3},
					{2, 0, 0, 3, 1},
			}};
	index_t index1_ex = {.ligne=0, .colonne=3};
	index_t index2_ex = {.ligne=2, .colonne=1};
	index_t index3_ex = {.ligne=42, .colonne=42};
	index_t index4_ex = {.ligne=0, .colonne=4};
	vector<int> tableau1_ex = {0, 3};
	vector<int> tableau2_ex = {2, 1, 3};

	FonctionsDeConversions_test();
	verifierIndexDansPlateau_test(plateau_ex, index1_ex, index2_ex, index3_ex);
	verifierCaseVide_test(plateau_ex, index1_ex, index2_ex, index3_ex);
	nonEncercle_test(plateau_ex, index2_ex, index4_ex);
	return 0;
}
