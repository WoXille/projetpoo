#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <optional>

#include <fstream>
#include <string>
#include <sstream>

#include "CellVivante.hpp"
#include "CellMorte.hpp"
#include "Grille.hpp"
#include "game.hpp"
#include "Regle.hpp"

using namespace std;

int main() {
    Regle Regles;
    int rep; 
    int max_generations;
    int generation_count = 0;

    cout << "=====================================================\n";
    cout << "          Bienvenue dans le Jeu de la Vie\n";
    cout << "======================================================\n\n";

    while (rep != 1 && rep != 2) {
        cout << "Veuillez choisir votre mode de jeu :\n";
        cout << "  1 - Mode automatique\n";
        cout << "  2 - Nombre predefini de generations\n";
        cout << "Votre choix : ";
        cin >> rep;
        cout << "\n";
    }

    if (rep == 2) {
        cout << "----------------------------------------\n";
        cout << "Combien de generations souhaitez-vous ?\n";
        cout << "Entrez un nombre : ";
        cin >> max_generations;
        cout << "----------------------------------------\n\n";

        Regles.set_max_generations(max_generations);
        Regles.x_generation();
    }

    rep = 3;
    while (rep != 1 && rep != 2) {
        cout << "Veuillez choisir votre mode d'affichage :\n";
        cout << "  1 - Affichage console\n";
        cout << "  2 - Affichage graphique\n";
        cout << "Votre choix : ";
        cin >> rep;
        cout << "\n";
    }

    if (rep == 1) {
        Regles.afficher();
    }

    rep = 3;
    while (rep != 1 && rep != 2) {
        cout << "Veuillez choisir la methode d'initialisation :\n";
        cout << "  1 - Initialisation vide\n";
        cout << "  2 - Initialisation via un fichier\n";
        cout << "Votre choix : ";
        cin >> rep;
        cout << "\n";
    }

    string ligne;
    string filename;

    cout << "Veuillez entrer le nom du fichier (avec extension) :\n";
    cout << "Nom du fichier : ";
    cin >> filename;


    ifstream fichier(filename);
    getline(fichier, ligne);
    ligne.shrink_to_fit();
    int pos = ligne.find(' ');
    const int largeur = stoi(ligne.substr(pos + 1));
    const int longueur = stoi(ligne.substr(0, pos));
    const int cellSize = 20;
    Game game(largeur,longueur);
    for (int i = 0; i < longueur; i++) {
        getline(fichier, ligne);
        for (int j = 0; j < largeur; j++) {
            if (ligne[j*2] == '1') {
                game.getCell(j, i)->RendreVivante();
            }
        }
    }
        
    
    
    
    cout << "Jeu cree avec une grille de " << longueur << "x" << largeur << "." << endl;

    sf::Clock clock;
    sf::Clock clock2;

    // Petit jeu pour le menu (10x10)
    Game game2(10, 10);
    sf::RenderWindow window2(
        sf::VideoMode(sf::Vector2u(400, 400)),
        "Menu Game of Life"
    );
    game2.startmenu(window2);

    // Fenêtre principale : largeur en X, longueur en Y
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(
            static_cast<unsigned int>(largeur  * cellSize), // largeur = X
            static_cast<unsigned int>(longueur * cellSize)  // longueur = Y
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
            if (Regles.is_generation()) {
                generation_count++;
                if (generation_count >= Regles.get_max_generations()) {
                    running = false;
                }
            }   

            // Gestion souris
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            int x = pos.x / cellSize; // colonne
            int y = pos.y / cellSize; // ligne

            // bornes : 0 <= x < largeur, 0 <= y < longueur
            if (x >= 0 && x < largeur && y >= 0 && y < longueur) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    game.getCell(x, y)->RendreVivante();
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
                    game.getCell(x, y)->RendreMorte();
                }
            }
        }

        // Contrôles clavier
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            running = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
            running = true;
        }

        // Mise à jour logique toutes les 100ms
        if (clock.getElapsedTime() >= sf::milliseconds(100) && running) {
            game.display();
            game.runIteration();
            clock.restart();
        }

        // Rendu toutes les 10ms (ou plus souvent)
        if (clock2.getElapsedTime() >= sf::milliseconds(10)) {
            game.renderGrid(window, cellSize);
            clock2.restart();
        }
    }

    return 0;
}
