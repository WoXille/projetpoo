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
    for (int i = 0; i < grille.getLargeur(); ++i) {
        for (int j = 0; j < grille.getHauteur(); ++j) {
            Cell* cell = grille.getCell(i, j);
            int voisinsVivants = grille.iteration(cell);
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