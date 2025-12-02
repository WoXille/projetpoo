#ifndef GRILLE_HPP
#define GRILLE_HPP

#include "Cell.hpp"
#include <iostream>

// Classe représentant la grille du Jeu de la Vie.
// Elle contient un tableau 2D de pointeurs vers des objets Cell,
// et permet l’accès ainsi que l’évolution de la grille.
class Grille {
private:
    int largeur;                    // Nombre de colonnes dans la grille
    int hauteur;                    // Nombre de lignes dans la grille
    Cell* tabcell[100][100];        // Tableau statique de pointeurs vers Cell

public:
    // Constructeur prenant la largeur et la hauteur de la grille.
    // L’initialisation complète des cellules est réalisée dans init().
    Grille(int l, int h);

    // Destructeur : libère la mémoire allouée aux cellules.
    ~Grille();

    // Initialise toutes les cellules :
    // allocation dynamique et état initial défini dans la classe Cell.
    void init();

    // Accesseurs pour les dimensions de la grille.
    int getLargeur() const {
        return largeur;
    }

    int getHauteur() const {
        return hauteur;
    }

    // Accès à une cellule située aux coordonnées (x, y).
    Cell* getCell(int x, int y) const;

    // Renvoie le nombre de voisins vivants de la cellule passée en paramètre.
    // Calcul réalisé avec gestion des bords en tore.
    int iteration(Cell* cell);

    // Renvoie un pointeur sur la première ligne du tableau 2D de cellules.
    // Méthode utilisée pour accéder aux données brutes du tableau si nécessaire.
    Cell** gettabcell() {
        return *tabcell;
    } 
};

#endif // GRILLE_HPP
