#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "Grille.hpp"

class Game {
 public:
    Game(int largeur, int hauteur, Cell** existingCells = nullptr);
    ~Game();

    void init();
    void runIteration();
    void display() const;
    Cell* getCell(int x, int y) const;
    void test();
    Game* clone() const;
    Grille getGrille() const;

    private:
    Grille grille;
};

#endif

