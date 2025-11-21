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

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                int x = pos.x / cellSize;
                int y = pos.y / cellSize;
                cout << "Clic en : " << x << ", " << y << endl;
                if (x==0 && y==0){
                    for (int i = 0; i < 1000; ++i) {
                        game.runIteration();
                        sf::sleep(sf::milliseconds(10));
                        game.renderGrid(window); 
                    }
                    
                }
                else {
                    game.getCell(x, y)->InverserVie();
                }
            }
        }

<<<<<<< HEAD
        game.renderGrid(window);    
         
=======
        if (clock.getElapsedTime() >= sf::milliseconds(100)) {
        game.runIteration();
        clock.restart();
    }
        game.renderGrid(window);       
>>>>>>> 3c33f9a1281698aaba7afff06a60d0be9279bed7
    }


    return 0;
}
