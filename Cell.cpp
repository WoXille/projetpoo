#include "Cell.hpp"

Cell::Cell(int xCoord, int yCoord)
    : x(xCoord), y(yCoord), etat(new CellMorte()) {}

Cell::~Cell() {
    delete etat;
}

void Cell::RendreVivante() {
    delete etat;
    etat = new CellVivante();
}

void Cell::RendreMorte() {
    delete etat;
    etat = new CellMorte();
}

void Cell::InverserVie() {
    if (etat->estVivante()) {
        delete etat;
        etat = new CellMorte();
    } else {
        delete etat;
        etat = new CellVivante();
    }
}
