#include "Cell.hpp"

// Constructeur : initialise une cellule aux coordonnées (xCoord, yCoord)
// et définit son état initial comme "morte".
Cell::Cell(int xCoord, int yCoord)
    : x(xCoord), y(yCoord), etat(new CellMorte()) {}

// Destructeur : libère la mémoire associée à l'état de la cellule.
// Cela évite les fuites mémoire puisque 'etat' est alloué dynamiquement.
Cell::~Cell() {
    delete etat;
}

// Méthode permettant de modifier la cellule pour la rendre vivante.
// L'ancien état est supprimé puis remplacé par un nouvel objet CellVivante.
void Cell::RendreVivante() {
    delete etat;
    etat = new CellVivante();
}

// Méthode permettant de modifier la cellule pour la rendre morte.
// Même logique que pour RendreVivante() : remplacement dynamique de l'état.
void Cell::RendreMorte() {
    delete etat;
    etat = new CellMorte();
}

// Méthode permettant de définir la cellule comme vivante "obstacle".
// Un obstacle correspond à un état particulier empêchant certaines interactions
// (selon les règles éventuelles implémentées ailleurs dans le projet).
void Cell::RendreObstacle_Vivante() {
    delete etat;
    etat = new CellVivante_Obstacle();
}

// Méthode permettant de définir la cellule comme morte "obstacle".
// Même logique que précédemment : changement de l'état interne de la cellule.
void Cell::RendreObstacle_Morte() {
    delete etat;
    etat = new CellMorte_Obstacle();
}
