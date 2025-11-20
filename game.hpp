#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Grille.hpp"

class Game {
 public:
    Game(int largeur, int hauteur);
    ~Game();

    void init();
    void runIteration();
    void display() const;
    Cell* getCell(int x, int y) const;
    void test();
    void renderGrid(sf::RenderWindow& window);

    private:
    Grille grille;
};

#endif

