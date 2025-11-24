#ifndef CELL_HPP
#define CELL_HPP

#include "CellEtat.hpp"
#include "CellVivante.hpp"
#include "CellMorte.hpp"

class Cell {
private:
    int x;
    int y;
    CellEtat* etat;

public:
    Cell(int xCoord, int yCoord);
    ~Cell();

    // Accesseurs
    int getX() const { return x; }
    int getY() const { return y; }


    void RendreVivante();
    void RendreMorte();
    bool estVivante() const { return etat->estVivante(); }
};

#endif // CELL_HPP
