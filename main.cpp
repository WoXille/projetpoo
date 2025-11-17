#include <iostream>
#include <memory>

#include "CellVivante.hpp"
#include "CellMorte.hpp"

int main() {
    // Création d'une cellule vivante
    CellEtat* s1 = new CellVivante();
    // Création d'une cellule morte
    CellEtat* s2 = new CellMorte();


    std::cout << "s1 est vivante ? " << s1->estVivante() << std::endl;
    std::cout << "s2 est vivante ? " << s2->estVivante() << std::endl;

    return 0;
}
