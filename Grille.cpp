#include "Grille.hpp"
#include "Cell.hpp" 

using namespace std;

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

Cell* Grille::getCell(int x, int y) const {
    return tabcell[x][y];
}

void Grille::init() {
    for (int i = 0; i < largeur; ++i) {
        for (int j = 0; j < hauteur; ++j) {
            tabcell[i][j] = new Cell(i, j);
        }
    }
}

int Grille::iteration(Cell* cell) {

    int x = cell->getX();
    int y = cell->getY();
    int voisinsVivants = 0;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;

            int voisinX = x + i;
            int voisinY = y + j;
            if (voisinX < 0){
                voisinX = largeur -1;
            }
            if (voisinX >= largeur){
                voisinX = 0;
            }
            if (voisinY < 0){
                voisinY = hauteur -1;
            }
            if (voisinY >= hauteur){
                voisinY = 0;
            }
            if (tabcell[voisinX][voisinY]->estVivante()) {
                voisinsVivants++;
            }
            
        }
    }
    return voisinsVivants;
}

