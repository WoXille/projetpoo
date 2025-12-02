#ifndef CELLMORTE_HPP
#define CELLMORTE_HPP

#include "CellEtat.hpp"

// État représentant une cellule morte standard.
// Elle ne participe plus aux interactions du jeu tant qu'elle ne renaît pas.
class CellMorte : public CellEtat {
public:

    // La cellule n'est pas vivante.
    bool estVivante() const override {
        return false;
    }

    // Une cellule morte classique n'est pas non plus un obstacle.
    bool estObstacle() const override {
        return false;
    }

    // Création d'une copie polymorphique de cet état.
    CellEtat* clone() const override {
        return new CellMorte(*this);
    }
};

#endif
