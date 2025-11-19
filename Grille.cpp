#include "Grille.hpp"
#include "Cell.hpp" 

Grille::Grille(int l, int h)
    : largeur(l), hauteur(h)
{
    init();
}

Grille::~Grille() {

    // On libère toutes les cellules allouées
    for (int i = 0; i < largeur; ++i) {
        for (int j = 0; j < hauteur; ++j) {
            delete tabcell[i][j];
        }
    }
}

void Grille::init() {
    for (int i = 0; i < largeur; ++i) {
        for (int j = 0; j < hauteur; ++j) {
            tabcell[i][j] = new Cell(i, j);
        }
    }
}

int Grille::iteration(Cell* cell) {
    int tmp = 0;
    int cx = cell->getX();
    int cy = cell->getY();

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue; // on ignore la cellule elle-même

            int nx = cx + dx;
            int ny = cy + dy;

            // on vérifie qu'on reste dans les bornes de la grille
            if (nx >= 0 && nx < largeur &&
                ny >= 0 && ny < hauteur) {
                if (tabcell[nx][ny]->estVivante()) {
                    tmp++;
                }
            }
        }
    }
    return tmp;
}

