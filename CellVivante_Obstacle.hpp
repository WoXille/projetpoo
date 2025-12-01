#ifndef CELLVIVANTE_OBSTACLE_HPP
#define CELLVIVANTE_OBSTACLE_HPP

#include "CellEtat.hpp"

class CellVivante_Obstacle : public CellEtat {
public:
    bool estVivante() const override {
        return true;
    }
    bool estObstacle() const override {
        return true;
    }
    CellEtat* clone() const override {
        return new CellVivante_Obstacle(*this);
    }
};

#endif