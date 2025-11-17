#ifndef CELLVIVANTE_HPP
#define CELLVIVANTE_HPP

#include "CellEtat.hpp"

class CellVivante : public CellEtat {
public:
    bool estVivante() const override {
        return true;
    }
    CellEtat* clone() const override {
        return new CellVivante(*this);
    }
};

#endif