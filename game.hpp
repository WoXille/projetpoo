#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include <string>

#include "Grille.hpp"
#include "Regle.hpp"
class Game {
 public:
    Game(int largeur, int hauteur);
    ~Game();

    void init();
    void runIteration(Regle * Regles);
    void display(int generation, std::string filename) const;
    Cell* getCell(int x, int y) const;
    void test();
    void renderGrid(sf::RenderWindow& window, int CellSize);
    void startmenu(sf::RenderWindow& window);
    void startmusic() { music.play(); };
    void stopmusic() { music.stop(); }
    int getMode() const { return mode; }
    void setMode(int m) { mode = m; }

    private:
    Grille grille;
    sf::Music music;
    sf::Font Roboto;
    sf::Font Cherolina;
    sf::Font AstonScript;
    int mode = 0; // 0 = normal, 1 = glider, 2 = helicopter
};

#endif

