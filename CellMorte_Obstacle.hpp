#ifndef CELLMORTE_OBSTACLE_HPP
#define CELLMORTE_OBSTACLE_HPP

#include "CellEtat.hpp"

// État représentant une cellule morte qui agit comme un obstacle.
// Ce type de cellule ne pourra pas être considérée dans l'évolution
// normale du jeu selon les règles appliquées.
class CellMorte_Obstacle : public CellEtat {
public:

    // Indique que cette cellule n'est pas vivante.
    bool estVivante() const override {
        return false;
    }

    // Indique qu'il s'agit bien d'un obstacle.
    bool estObstacle() const override {
        return true;
    }

    // Retourne une copie polymorphique de l'état.
    CellEtat* clone() const override {
        return new CellMorte_Obstacle(*this);
    }
};

#endif
