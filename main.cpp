#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Text.hpp>
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
    sf::Clock clock;
    sf::Clock clock2;

    Game game(longueur,largeur);


    Game game2(10,10);
    sf::RenderWindow window2(
        sf::VideoMode(sf::Vector2u(400, 400)),
        "Menu Game of Life"
    );
    game2.startmenu(window2);








    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(
            static_cast<unsigned int>(largeur * cellSize),
            static_cast<unsigned int>(longueur * cellSize)
        )),
        "Game of Life"
    );

    //game.startmusic();
    bool running = true;
    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            sf::Vector2i pos = sf::Mouse::getPosition(window);
                int x = pos.x / 10;
                int y = pos.y / 10;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                game.getCell(x, y)->RendreVivante();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
                game.getCell(x, y)->RendreMorte();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            running = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
            running = true;
        }
        


        if (clock.getElapsedTime() >= sf::milliseconds(100) && running == true) {
        game.runIteration();
        clock.restart();
        }
        if (clock2.getElapsedTime() >= sf::milliseconds(10)) {
        game.renderGrid(window); 
        clock2.restart();
        }

    }
    return 0;
}
