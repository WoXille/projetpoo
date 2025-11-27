#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>

#include "Grille.hpp"

class Game {
 public:
    Game(int largeur, int hauteur);
    ~Game();

    void init();
    void runIteration();
    void display(int generation) const;
    Cell* getCell(int x, int y) const;
    void test();
    void renderGrid(sf::RenderWindow& window, int CellSize);
    void startmenu(sf::RenderWindow& window);
    void startmusic();

    private:
    Grille grille;
    sf::Music music;
};

#endif

