#ifndef GRILLE_HPP
#define GRILLE_HPP

#include "Cell.hpp"
#include <iostream>

class Grille {
private:
    int largeur;
    int hauteur;
    Cell* tabcell[100][100]; // tableau de pointeurs vers Cell

public:
    Grille(int l, int h);
    ~Grille();

    // Initialisation de la grille
    void init();

    int getLargeur() const {
        return largeur;
    }

    int getHauteur() const {
        return hauteur;
    }

    Cell* getCell(int x, int y) const;

    int iteration(Cell* cell);

    Cell** gettabcell() {
        return *tabcell;
    } 


};

#endif // GRILLE_HPP
