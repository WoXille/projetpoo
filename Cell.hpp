#ifndef CELL_HPP
#define CELL_HPP

#include "CellEtat.hpp"
#include "CellVivante.hpp"
#include "CellMorte.hpp"
#include "CellVivante_Obstacle.hpp"
#include "CellMorte_Obstacle.hpp"

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
    void RendreObstacle_Vivante();
    void RendreObstacle_Morte();
    bool estVivante() const { return etat->estVivante();}
    bool estObstacle() const{ return etat->estObstacle(); }
};

#endif // CELL_HPP
