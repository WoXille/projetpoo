#ifndef CELLVIVANTE_OBSTACLE_HPP
#define CELLVIVANTE_OBSTACLE_HPP

#include "CellEtat.hpp"

// État représentant une cellule vivante qui agit comme un obstacle.
// Ce type de cellule reste vivante mais peut empêcher certaines évolutions
// selon les règles spécifiques définies ailleurs.
class CellVivante_Obstacle : public CellEtat {
public:

    // Indique que la cellule est vivante.
    bool estVivante() const override {
        return true;
    }

    // Indique qu’il s’agit d’un obstacle.
    bool estObstacle() const override {
        return true;
    }
};

#endif
