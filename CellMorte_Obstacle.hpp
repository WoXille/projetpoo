#ifndef CELLMORTE_OBSTACLE_HPP
#define CELLMORTE_OBSTACLE_HPP

#include "CellEtat.hpp"

class CellMorte_Obstacle : public CellEtat {
public:
    bool estVivante() const override {
        return false;
    }
    bool estObstacle() const override {
        return true;
    }
    CellEtat* clone() const override {
        return new CellMorte_Obstacle(*this);
    }
};

#endif
