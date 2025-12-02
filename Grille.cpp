#include "Grille.hpp"
#include "Cell.hpp" 

using namespace std;

// Constructeur : définit la taille de la grille puis initialise toutes les cellules.
Grille::Grille(int l, int h)
    : largeur(l), hauteur(h)
{
    init();
}

// Destructeur : libère toutes les cellules allouées dynamiquement
// afin d'éviter les fuites mémoire.
Grille::~Grille() {
    for (int i = 0; i < largeur; ++i) {
        for (int j = 0; j < hauteur; ++j) {
            delete tabcell[i][j];
        }
    }
}

// Renvoie un pointeur vers la cellule située aux coordonnées (x, y).
Cell* Grille::getCell(int x, int y) const {
    return tabcell[x][y];
}

// Création et allocation de chaque cellule de la grille.
// Chaque cellule est placée dans un tableau 2D de pointeurs.
void Grille::init() {
    for (int i = 0; i < largeur; ++i) {
        for (int j = 0; j < hauteur; ++j) {
            tabcell[i][j] = new Cell(i, j);
        }
    }
}

// Calcule le nombre de voisins vivants pour la cellule passée en paramètre.
// Ce calcul applique un comportement de bord en "tore" :
// les cellules situées aux extrémités considèrent les bords opposés comme voisins(attendu bonus)
int Grille::iteration(Cell* cell) {

    int x = cell->getX();
    int y = cell->getY();
    int voisinsVivants = 0;

    // Parcours des 8 voisins autour de la cellule (x, y).
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i==0 && j==0) continue; // Ignorer la cellule elle-même.
    
            int voisinX = x + i;
            int voisinY = y + j;

            // Gestion des bords avec effet de tore.
            if (voisinX < 0) {
                voisinX = largeur - 1;
            }
            if (voisinX >= largeur) {
                voisinX = 0;
            }
            if (voisinY < 0) {
                voisinY = hauteur - 1;
            }
            if (voisinY >= hauteur) {
                voisinY = 0;
            }

            // Comptage uniquement si la cellule voisine est vivante.
            if (tabcell[voisinX][voisinY]->estVivante()) {
                voisinsVivants++;
            }
        }
    }

    // Retour du nombre total de voisins vivants détectés.
    return voisinsVivants;
}
