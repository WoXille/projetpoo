#ifndef CELLVIVANTE_HPP
#define CELLVIVANTE_HPP

#include "CellEtat.hpp"

// État représentant une cellule vivante classique dans le jeu.
// Elle participe entièrement aux règles de reproduction et de survie.
class CellVivante : public CellEtat {
public:

    // La cellule est vivante.
    bool estVivante() const override {
        return true;
    }

    // Ce type de cellule n'est pas considéré comme un obstacle.
    bool estObstacle() const override {
        return false;
    }
};

#endif
