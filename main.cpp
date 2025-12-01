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
#include "CellVivante_Obstacle.hpp"
#include "CellMorte_Obstacle.hpp"
#include "Grille.hpp"
#include "game.hpp"
#include "Regle.hpp"

using namespace std;

int main() {
    Regle Regles;
    int rep=0; 
    int max_generations;
    int generation_count = 0;
    string ligne;
    string filename;
    ifstream fichier;

    cout << "======================================================"<< endl;
    cout << "          Bienvenue dans le Jeu de la Vie" << endl;
    cout << "======================================================"<< endl;

    while (rep != 1 && rep != 2) {
        cout << "Souhaitez-vous jouer ou changer les regles?" << endl;
        cout << "  1 - Je veux jouer" << endl;
        cout << "  2 - Je veux parametrer les regles" << endl;
        cout << "Votre choix : ";
        cin >> rep;
        cout << "\n";
        if (rep==2){
            while (rep == 2 || rep == 1) {
                cout << "Quelles regles souhaitez-vous modifier?" << endl;
                cout << "  1 - Regle de naissance" << endl;
                cout << "  2 - Regle de mort" << endl;
                cout << "  3 - Retour au menu precedent" << endl;
                cout << "Votre choix : ";
                cin >> rep;
                cout << "\n";
                if (rep == 1) {
                    int naissance;
                    cout << "Entrez le nombre de voisins necessaires pour la naissance d'une cellule : ";
                    cin >> naissance;
                    Regles.set_rules(Regles.get_voisins_max(), Regles.get_voisins_min(), naissance);
                    cout << "\n";
                }
                else if (rep == 2) {
                    int voisins_min, voisins_max;
                    cout << "Entrez le nombre minimum de voisins pour qu'une cellule vive survive : ";
                    cin >> voisins_min;
                    cout << "Entrez le nombre maximum de voisins pour qu'une cellule vive survive : ";
                    cin >> voisins_max;
                    if (voisins_min > voisins_max) {
                        cout << "Erreur : le nombre minimum de voisins ne peut pas etre superieur au nombre maximum." << endl << endl;
                        Regles.set_rules(voisins_min, voisins_max, Regles.get_naissance());
                        rep = 3;
                    } else {
                        Regles.set_rules(voisins_max, voisins_min, Regles.get_naissance());
                        cout << "\n";
                    }
                    
                }
            }
        }   
    }
    rep = 3;
    while (rep != 1 && rep != 2) {
        cout << "Veuillez choisir votre mode de jeu :" << endl;
        cout << "  1 - Nombre predefini de generations" << endl;
        cout << "  2 - Mode automatique" << endl;
        cout << "Votre choix : ";
        cin >> rep;
        cout << "\n";
    }
    
    if (rep == 1) {
        cout << "----------------------------------------" << endl;
        cout << "Combien de generations souhaitez-vous ?" << endl;
        cout << "Entrez un nombre : ";
        cin >> max_generations;
        cout << "----------------------------------------" << endl << endl;
        Regles.set_max_generations(max_generations);
        Regles.x_generation();
        rep = 3;
    }

    
    while (rep != 1 && rep != 2) {
        cout << "Veuillez choisir votre mode d'affichage :" << endl;
        cout << "  1 - Affichage console" << endl;
        cout << "  2 - Affichage graphique" << endl;
        cout << "Votre choix : ";
        cin >> rep;
        cout << endl;
    }
    if (rep==2){
        Regles.afficher();
        rep = 3;
    }   
    else {
        rep =2;
    }

    
    while (rep != 1 && rep != 2) {
        cout << "Veuillez choisir la methode d'initialisation :" << endl;
        cout << "  1 - Initialisation vide" << endl;
        cout << "  2 - Initialisation via un fichier" << endl;
        cout << "Votre choix : ";
        cin >> rep;
        cout << endl;
    }
    
    int pos;
    if (rep == 1) {
        cout << "Veuillez saisir la longueur que vous souhaitez :" << endl;
        cin >> ligne;
        ligne += " "; 
        cout << "Maintenant, veuillez saisir la largeur que vous souhaitez :" << endl;
        cin >> filename;
        ligne += filename;
        pos = ligne.find(' ');


    }
    if (rep == 2) {
        cout << "Veuillez entrer le nom du fichier a charger (avec extension) :" << endl;
        cout << "Nom du fichier : ";
        cin >> filename;
        fichier.open(filename);
        getline(fichier, ligne);
        ligne.shrink_to_fit();
        pos = ligne.find(' ');
    }
    
    const int largeur = stoi(ligne.substr(pos + 1));
    const int longueur = stoi(ligne.substr(0, pos));
    cout << "Dimensions de la grille : " << longueur << " x " << largeur << endl << endl;
    const int cellSize = 20;
    Game game(largeur,longueur);
    cout << "init grille" << endl;
    if (rep == 2) {
        for (int i = 0; i < longueur; i++) {
            getline(fichier, ligne);
            for (int j = 0; j < largeur; j++) {
                if (ligne[j*2] == '1') {
                    game.getCell(j, i)->RendreVivante();
                }
            }
        }
    }   
    
    

    sf::Clock clock;
    sf::Clock clock2;

    // Petit jeu pour le menu (10x10)

    int hauteurgrid;

    // Fenêtre principale : largeur en X, longueur en Y
    if (longueur * cellSize < 600) {
        hauteurgrid = 600;
    } else {
        hauteurgrid = longueur * cellSize;
    }
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(
            static_cast<unsigned int>((largeur  * cellSize)+600), // largeur = X
            static_cast<unsigned int>(hauteurgrid)  // longueur = Y
        )),
        "Game of Life"
    );
    bool running = true;

    if (Regles.is_afficher()){
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
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G)) {
                        game.getCell(x+1, y+1)->RendreVivante();
                        game.getCell(x+1, y)->RendreVivante();
                        game.getCell(x+1, y-1)->RendreVivante();
                        game.getCell(x-1, y)->RendreVivante();
                        game.getCell(x, y-1)->RendreVivante();
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
                        game.getCell(x, y+1)->RendreVivante();
                        game.getCell(x, y)->RendreVivante();
                        game.getCell(x, y-1)->RendreVivante();
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
                        for (int i = 0; i < largeur; ++i) {
                            for (int j = 0; j < longueur; ++j) {
                                game.getCell(i, j)->RendreMorte();
                            }
                        }
                    }
                    
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U)) {
                        game.getCell(x,y)->RendreObstacle_Vivante();
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) {
                        game.getCell(x,y)->RendreObstacle_Morte();
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
                game.startmusic();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
                game.stopmusic();
            }

            // Mise à jour logique toutes les 100ms
            if (clock.getElapsedTime() >= sf::milliseconds(100) && running) {
                game.runIteration(&Regles);
                clock.restart();
            }

            // Rendu toutes les 10ms (ou plus souvent)
            if (clock2.getElapsedTime() >= sf::milliseconds(10)) {
                game.renderGrid(window, cellSize);
                clock2.restart();
            }
            
        }
    } else {
        int loc = filename.find_last_of('.');
        filename=filename.substr(0, loc);
        filename+="_out.txt";
        for (int i=0; i<=Regles.get_max_generations(); i++){
            game.display(i, filename);
            game.runIteration(&Regles);
        }
    }
    return 0;
}
