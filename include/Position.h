#ifndef AMAZONES_POSITION_H
#define AMAZONES_POSITION_H

#include <vector>
#include "Plateau.h"

using namespace std;

vector<index_t> calculerPositionsDiagonales(index_t positionInitiale, plateau_t plateau);
vector<index_t> calculerPositionsOrthogonales(index_t positionInitiale, plateau_t plateau);
vector<index_t> calculerPositionsCheval(index_t positionInitiale, plateau_t plateau);

#endif //AMAZONES_POSITION_H
