#ifndef CELLMORTE_HPP
#define CELLMORTE_HPP

#include "CellEtat.hpp"

class CellMorte : public CellEtat {
public:
    bool estVivante() const override {
        return false;
    }
    CellEtat* clone() const override {
        return new CellMorte(*this);
    }
};

#endif
