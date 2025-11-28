#include "game.hpp"

#include <fstream>
#include <iostream>

using namespace std;

Game::Game(int largeur, int hauteur)
    : grille(largeur, hauteur) {
    init();
}

Game::~Game() {
}

void Game::init() {
    grille.init();
}

void Game::test() {
    grille.getCell(0,0)->RendreVivante();
    cout << grille.getCell(0,0)->estVivante() << endl;
    cout << grille.getCell(0,1)->estVivante() << endl;
}


void Game::runIteration(Regle * Regles) {
    int tempTab[100][100];
    for (int i = 0; i < grille.getLargeur(); ++i) {
        for (int j = 0; j < grille.getHauteur(); ++j) {
            Cell* cell = grille.getCell(i, j);
            tempTab[i][j] = grille.iteration(cell);
        }
    }

    for (int i = 0; i < grille.getLargeur(); ++i) {
        for (int j = 0; j < grille.getHauteur(); ++j) {
            Cell* cell = grille.getCell(i, j);
            int voisinsVivants = tempTab[i][j];

            if (!(cell->estVivante()) && voisinsVivants == Regles->get_naissance()) {
                cell->RendreVivante();
            } else if (cell->estVivante() && (voisinsVivants < Regles->get_voisins_min() || voisinsVivants > Regles->get_voisins_max())) {
                cell->RendreMorte();
            }
        }
    }
}

void Game::display(int generation) const {
    ofstream fichier("output.txt", ios::app);
    if (!fichier.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier output.txt" << endl;
        return;
    }
    fichier << "Generation :" << generation << endl;
    for (int j = 0; j < grille.getHauteur(); ++j) {
        for (int i = 0; i < grille.getLargeur(); ++i) {
            Cell* cell = grille.getCell(i, j);
            if (cell->estVivante()) {
                fichier << "1 ";
            } else {
                fichier << "0 ";
            }
        }
        fichier << endl;
    }
    fichier << endl; // Ajouter une ligne vide entre les générations
    fichier.close();
}

Cell* Game::getCell(int x, int y) const {
    return grille.getCell(x, y);
}

void Game::renderGrid(sf::RenderWindow& window, int CellSize) {
    window.clear();
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    

    sf::RectangleShape cellShape(sf::Vector2f(CellSize - 1.0f, CellSize - 1.0f));
    for (int x = 0; x < grille.getLargeur(); ++x) {
        for (int y = 0; y < grille.getHauteur(); ++y) {
                cellShape.setPosition(sf::Vector2f(
                    static_cast<float>(x * CellSize),
                    static_cast<float>(y * CellSize)));
            if (grille.getCell(x, y)->estVivante()) {
                cellShape.setFillColor(sf::Color::White);
                window.draw(cellShape);
            }
            if (pos.x / CellSize == x && pos.y / CellSize == y) {
                cellShape.setFillColor(sf::Color(255, 0, 0, 100)); // Rouge semi-transparent
                window.draw(cellShape);
        }
    }
}

    window.display();
}
 void Game::startmusic() {
    if (!music.openFromFile("assets/music/kahoot_music.ogg")) {  // on va parler du .ogg plus bas
        std::cerr << "Erreur lors du chargement de la musique." << std::endl;
        return;
    }
    music.setLooping(true);
    music.setVolume(100.f); // au cas où
    music.play();
}

void Game::startmenu(sf::RenderWindow& window) {
    window.clear(sf::Color::Blue);

    // Charger la police depuis un fichier
    sf::Font font;
    if (!font.openFromFile("assets/fonts/Roboto-Bold.ttf")) {
        cerr << "Erreur : impossible de charger Roboto-Bold.ttf" << endl;
        return;
    }

    // Fond du titre
    sf::RectangleShape titleBackground(sf::Vector2f(400.f, 80.f));
    titleBackground.setFillColor(sf::Color::Blue);
    titleBackground.setPosition(sf::Vector2f(0.f, 0.f));

    // Textes du menu
    sf::Text text(font, "Game of Life Menu", 24);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(50.f, 50.f));

    window.draw(titleBackground);
    window.draw(text);
    window.display();
}

