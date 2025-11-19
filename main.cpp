#include <iostream>
#include <memory>

#include "CellVivante.hpp"
#include "CellMorte.hpp"
#include "Grille.hpp"

int main() {

    Grille grille(10,10);

    // Création d'une cellule vivante
    CellEtat* s1 = new CellVivante();
    // Création d'une cellule morte
    CellEtat* s2 = new CellMorte();


    std::cout << "s1 est vivante ? " << s1->estVivante() << std::endl;
    std::cout << "s2 est vivante ? " << s2->estVivante() << std::endl;

    delete s1;
    delete s2;

    grille.getCell(5,5)->RendreVivante();
    std::cout << "Cellule (5,5) est vivante ? " << grille.getCell(5,5)->estVivante() << std::endl;
    std::cout << "Cellule (4,5) a " << grille.iteration(grille.getCell(4,5)) << " voisins vivants." << std::endl;

    return 0;
}
