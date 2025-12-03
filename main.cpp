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
    Regle Regles;                 // Objet contenant les règles du jeu (naissance, survie, etc.)
    int rep=0;                    // Variable de choix utilisateur
    int max_generations;          // Nombre maximum de générations (mode borné)
    int generation_count = 0;     // Compteur de générations en mode automatique
    string ligne;                 // Ligne lue au clavier ou dans un fichier
    string filename;              // Nom de fichier pour l'initialisation ou la sortie
    ifstream fichier;             // Flux d'entrée pour lire un fichier d'initialisation

    cout << "======================================================"<< endl;
    cout << "          Bienvenue dans le Jeu de la Vie" << endl;
    cout << "======================================================"<< endl;

    // Premier menu : jouer directement ou paramétrer les règles.
    while (rep != 1 && rep != 2) {
        cout << "Souhaitez-vous jouer ou changer les regles?" << endl;
        cout << "  1 - Je veux jouer" << endl;
        cout << "  2 - Je veux parametrer les regles" << endl;
        cout << "Votre choix : ";
        cin >> rep;
        cout << "\n";

        // Si l'utilisateur choisit de modifier les règles.
        if (rep==2){
            while (rep == 2 || rep == 1) {
                cout << "Quelles regles souhaitez-vous modifier?" << endl;
                cout << "  1 - Regle de naissance" << endl;
                cout << "  2 - Regle de mort" << endl;
                cout << "  3 - Retour au menu precedent" << endl;
                cout << "Votre choix : ";
                cin >> rep;
                cout << "\n";

                // Modification de la règle de naissance.
                if (rep == 1) {
                    int naissance;
                    cout << "Entrez le nombre de voisins necessaires pour la naissance d'une cellule : ";
                    cin >> naissance;
                    Regles.set_rules(Regles.get_voisins_max(), Regles.get_voisins_min(), naissance);
                    cout << "\n";
                }
                // Modification de la règle de mort (intervalle de survie).
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
                        // Attention : l'ordre des paramètres dans set_rules est (v_max, v_min, naissance).
                        Regles.set_rules(voisins_max, voisins_min, Regles.get_naissance());
                        cout << "\n";
                    }
                }
            }
        }   
    }

    // Menu suivant : choix du mode de jeu (générations bornées ou mode automatique).
    rep = 3;
    while (rep != 1 && rep != 2) {
        cout << "Veuillez choisir votre mode de jeu :" << endl;
        cout << "  1 - Nombre predefini de generations" << endl;
        cout << "  2 - Mode automatique" << endl;
        cout << "Votre choix : ";
        cin >> rep;
        cout << "\n";
    }
    
    // Mode avec nombre de générations prédéfini.
    if (rep == 1) {
        cout << "----------------------------------------" << endl;
        cout << "Combien de generations souhaitez-vous ?" << endl;
        cout << "Entrez un nombre : ";
        cin >> max_generations;
        cout << "----------------------------------------" << endl << endl;
        Regles.set_max_generations(max_generations);
        Regles.x_generation();          // Active le mode "limité en nombre de générations".
        rep = 3;
    }

    // Choix du mode d'affichage : console (fichier texte) ou graphique SFML.
    while (rep != 1 && rep != 2) {
        cout << "Veuillez choisir votre mode d'affichage :" << endl;
        cout << "  1 - Affichage console" << endl;
        cout << "  2 - Affichage graphique" << endl;
        cout << "Votre choix : ";
        cin >> rep;
        cout << endl;
    }
    if (rep==2){
        Regles.afficher();   // Active le mode graphique dans l'objet Regles.
        rep = 3;
    }   
    else {
        rep =2;              // Reste en mode console / fichier.
    }

    // Choix de la méthode d'initialisation : vide ou depuis un fichier.
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
        // Initialisation manuelle : l'utilisateur saisit longueur et largeur.
        cout << "Veuillez saisir la longueur que vous souhaitez :" << endl;
        cin >> ligne;
        ligne += " "; 
        cout << "Maintenant, veuillez saisir la largeur que vous souhaitez :" << endl;
        cin >> filename;
        ligne += filename;
        pos = ligne.find(' ');
    }
    if (rep == 2) {
        // Initialisation via un fichier : première ligne = "longueur largeur".
        cout << "Veuillez entrer le nom du fichier a charger (avec extension) :" << endl;
        cout << "Nom du fichier : ";
        cin >> filename;
        fichier.open(filename);
        getline(fichier, ligne);
        ligne.shrink_to_fit();
        pos = ligne.find(' ');
    }
    
    // Extraction des dimensions de la grille.
    const int largeur = stoi(ligne.substr(pos + 1));
    const int longueur = stoi(ligne.substr(0, pos));
    cout << "Dimensions de la grille : " << longueur << " x " << largeur << endl << endl;

    const int cellSize = 20;        // Taille graphique d'une cellule en pixels.
    Game game(largeur,longueur);    // Création de l'objet Game avec ces dimensions.

    // Si initialisation par fichier : lecture des lignes et activation des cellules vivantes.
    if (rep == 2) {
        for (int i = 0; i < longueur; i++) {
            getline(fichier, ligne);
            for (int j = 0; j < largeur; j++) {
                // Le fichier utilise "1 " ou "0 " -> index j*2 sur la ligne.
                if (ligne[j*2] == '1') {
                    game.getCell(j, i)->RendreVivante();
                }
            }
        }
    }   
    
    // Deux horloges SFML pour gérer :
    // - la fréquence de mise à jour logique (clock)
    // - la fréquence de rendu graphique (clock2).
    sf::Clock clock;
    sf::Clock clock2;

    // Calcul de la hauteur de la fenêtre pour s'assurer d'un minimum d'espace d'affichage.
    int hauteurgrid;

    // Fenêtre principale : largeur en X, longueur en Y (en pixels).
    if (longueur * cellSize < 600) {
        hauteurgrid = 600;
    } else {
        hauteurgrid = longueur * cellSize;
    }
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(
            static_cast<unsigned int>((largeur  * cellSize)+600), // largeur grille + panneau info
            static_cast<unsigned int>(hauteurgrid)
        )),
        "Game of Life"
    );
    bool running = true;   // Indique si la simulation avance ou est en pause.

    // Branche d'exécution pour l'affichage graphique.
    if (Regles.is_afficher()){
        while (window.isOpen()) {
            // Gestion des événements SFML (clavier, souris, fermeture).
            while (const std::optional<sf::Event> event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }

                // Gestion du mode "nombre de générations prédéfini".
                if (Regles.is_generation()) {
                    generation_count++;
                    if (generation_count >= Regles.get_max_generations()) {
                        running = false;
                    }
                }   

                // Gestion souris : conversion position pixel -> indices de cellule.
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                int x = pos.x / cellSize; // colonne
                int y = pos.y / cellSize; // ligne
                
                // Changement de mode via le clavier (N, G, H, O).
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
                    game.setMode(0); // Mode normal
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G)) {
                    game.setMode(1); // Mode Glider
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
                    game.setMode(2); // Mode Helicopter
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) {
                    game.setMode(3); // Mode Obstacle
                }
                
                int mode = game.getMode();

                // Vérification que la position souris se trouve dans la grille.
                // bornes : 0 <= x < largeur, 0 <= y < longueur
                if (x >= 0 && x < largeur && y >= 0 && y < longueur) {

                    // Mode normal : clic gauche -> cellule vivante, clic droit -> cellule morte.
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mode == 0) {
                        game.getCell(x, y)->RendreVivante();
                    }
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && mode == 0) {
                        game.getCell(x, y)->RendreMorte();
                    }

                    // Mode Glider : pose un motif "planeur" autour de la cellule ciblée.
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mode == 1) {
                        if (x+1 < largeur && y+1 < longueur && y-1 >=0 && x-1 >=0) {
                            game.getCell(x+1, y+1)->RendreVivante();
                            game.getCell(x+1, y)->RendreVivante();
                            game.getCell(x+1, y-1)->RendreVivante();
                            game.getCell(x-1, y)->RendreVivante();
                            game.getCell(x, y-1)->RendreVivante();
                        }
                    }

                    // Mode Helicopter : pose un motif linéaire vertical.
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mode == 2) {
                        if (y+1 < longueur && y-1 >=0) {
                            game.getCell(x, y+1)->RendreVivante();
                            game.getCell(x, y)->RendreVivante();
                            game.getCell(x, y-1)->RendreVivante();
                        }
                    }

                    // Touche C : efface toute la grille (toutes les cellules mortes).
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
                        for (int i = 0; i < largeur; ++i) {
                            for (int j = 0; j < longueur; ++j) {
                                game.getCell(i, j)->RendreMorte();
                            }
                        }
                    }
                    
                    // Mode Obstacle : clic gauche -> cellule vivante obstacle,
                    // clic droit -> cellule morte obstacle.
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mode == 3) {
                        game.getCell(x,y)->RendreObstacle_Vivante();
                    }
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && mode == 3) {
                        game.getCell(x,y)->RendreObstacle_Morte();
                    }
                }
            }

            // Contrôles clavier globaux (hors boucle d'événements).
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                running = false;   // Met en pause la simulation.
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                running = true;    // Relance la simulation.
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
                game.startmusic(); // Lance la musique.
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
                game.stopmusic();  // Arrête la musique.
            }

            // Mise à jour de la logique du jeu toutes les 100 ms, si running est vrai.
            if (clock.getElapsedTime() >= sf::milliseconds(100) && running) {
                game.runIteration(&Regles);
                clock.restart();
            }

            // Rendu graphique fréquent (toutes les 10 ms), pour eviter les abus de CPU.
            if (clock2.getElapsedTime() >= sf::milliseconds(10)) {
                game.renderGrid(window, cellSize);
                clock2.restart();
            }
        }
    }  else {
        // Branche "affichage console" : génération d'un fichier texte avec l'évolution.
        int loc = filename.find_last_of('.');
        filename=filename.substr(0, loc);
        filename+="_out.txt";

        for (int i=0; i<=Regles.get_max_generations(); i++){
            game.display(i, filename);      // Écrit la génération i dans le fichier.
            game.runIteration(&Regles);     // Calcule la génération suivante.
        }
    }

    return 0;
}
