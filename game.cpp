#include "game.hpp"



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


void Game::runIteration() {
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

            if (!(cell->estVivante()) && voisinsVivants == 3) {
                cell->RendreVivante();
            } else if (cell->estVivante() && (voisinsVivants < 2 || voisinsVivants > 3)) {
                cell->RendreMorte();
            }
        }
    }
}

void Game::display() const {
    for (int j = 0; j < grille.getHauteur(); ++j) {
        for (int i = 0; i < grille.getLargeur(); ++i) {
            Cell* cell = grille.getCell(i, j);
            if (cell->estVivante()) {
                cout << "1 ";
            } else {
                cout << "0 ";
            }
        }
        cout << endl;
    }
}

Cell* Game::getCell(int x, int y) const {
    return grille.getCell(x, y);
}

void Game::renderGrid(sf::RenderWindow& window) {
    window.clear();

    sf::RectangleShape cellShape(sf::Vector2f(10.0f - 1.0f, 10.0f - 1.0f));

    for (int x = 0; x < grille.getLargeur(); ++x) {
        for (int y = 0; y < grille.getHauteur(); ++y) {
            if (grille.getCell(x, y)->estVivante()) {
                cellShape.setPosition(sf::Vector2f(
                    static_cast<float>(x * 10),
                    static_cast<float>(y * 10)
                ));
                window.draw(cellShape);
            }
        }
    }

    window.display();
}
 void Game::startmusic() {
    if (!music.openFromFile("kahoot_music.ogg")) {  // on va parler du .ogg plus bas
        std::cerr << "Erreur lors du chargement de la musique." << std::endl;
        return;
    }
    music.setLooping(true);
    music.setVolume(100.f); // au cas où
    music.play();
}

void Game::startmenu(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    sf::RectangleShape titleBackground(sf::Vector2f(20.0f, 20.0f));
    sf::Text text( sf::Font("Roboto"),"Game of Life Menu", 24); // Utilisez une police valide ici
    titleBackground.setFillColor(sf::Color::Blue);
    titleBackground.setPosition(sf::Vector2f(0.0f, 0.0f));
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(50.0f, 50.0f));
    window.draw(titleBackground);
    window.draw(text);

    window.display();
    
}

