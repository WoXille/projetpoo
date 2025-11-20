#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <optional>

#include "CellVivante.hpp"
#include "CellMorte.hpp"
#include "Grille.hpp"
#include "game.hpp"

using namespace std;

int main() {
    const int longueur = 80;
    const int largeur = 80;
    const int cellSize = 10;

    Game game(longueur,largeur);
    game.getCell(4,5)->RendreVivante();
    game.getCell(5,5)->RendreVivante();
    game.getCell(6,5)->RendreVivante();
    game.test();
    cout << "Avant une itération :" << endl;
    game.runIteration();
    cout << "Après une itération :" << endl;

    game.getCell(8,8)->RendreVivante();
    game.getCell(10,8)->RendreVivante();
    game.getCell(9,9)->RendreVivante();
    game.getCell(10,9)->RendreVivante();
    game.getCell(9,10)->RendreVivante();
    










    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(
            static_cast<unsigned int>(largeur * cellSize),
            static_cast<unsigned int>(longueur * cellSize)
        )),
        "Game of Life"
    );

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        game.renderGrid(window);

        sf::sleep(sf::milliseconds(100));
        game.runIteration();    
    }


    return 0;
}
