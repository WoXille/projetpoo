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

// Classe principale de gestion du jeu de la vie
// Elle encapsule :
//  - la grille de cellules (Grille)
//  - les ressources graphiques et sonores (SFML)
//  - le mode d'édition / interaction (normal, glider, helicopter, obstacle...).
class Game {
 public:
    // Constructeur : crée la grille avec la largeur et la hauteur données,
    // puis initialise les ressources (voir Game::init()).
    Game(int largeur, int hauteur);

    // Destructeur.
    ~Game();

    // Initialise les ressources (polices, musique, grille...).
    void init();

    // Effectue une itération du jeu selon les règles passées en paramètre.
    // Utilise la Grille et l'objet Regle pour calculer la génération suivante.
    void runIteration(Regle * Regles);

    // Sauvegarde l'état de la grille dans un fichier texte
    // pour une génération donnée.
    void display(int generation, std::string filename) const;

    // Accès direct à une cellule de la grille via ses coordonnées.
    Cell* getCell(int x, int y) const;

    // Affiche la grille et l'interface utilisateur dans la fenêtre SFML.
    void renderGrid(sf::RenderWindow& window, int CellSize);

    // Contrôle de la musique d'ambiance.
    void startmusic() { music.play(); };
    void stopmusic() { music.stop(); }

    // Accès et modification du mode d'interaction :
    // 0 = normal, 1 = glider, 2 = helicopter, 3 = obstacle (dans l'implémentation).
    int getMode() const { return mode; }
    void setMode(int m) { mode = m; }

 private:
    Grille grille;        // Grille de cellules sur laquelle le jeu évolue.
    sf::Music music;      // Musique de fond.
    sf::Font Roboto;      // Police principale pour les textes d'information.
    sf::Font Cherolina;   // Police décorative (titre, etc.).
    sf::Font AstonScript; // Police pour le titre "Game of Life".
    int mode = 0;         // Mode d'édition / interaction actuel.
};

#endif
