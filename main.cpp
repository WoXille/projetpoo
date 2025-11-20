#include <iostream>
#include <memory>

#include "CellVivante.hpp"
#include "CellMorte.hpp"
#include "Grille.hpp"
#include "game.hpp"

using namespace std;

int main() {

    Game game(10,10);
    game.display();
    game.getCell(4,5)->RendreVivante();
    game.getCell(5,5)->RendreVivante();
    game.getCell(6,5)->RendreVivante();
    game.test();
    cout << "Avant une itération :" << endl;
    game.display();
    game.runIteration();
    cout << "Après une itération :" << endl;
    game.display();

    return 0;
}
