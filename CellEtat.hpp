#ifndef CELLETAT_HPP
#define CELLETAT_HPP

// Classe abstraite représentant l'état d'une cellule.
//  - La cellule ne contient qu'un pointeur vers CellEtat*
//  - Le comportement de la cellule dépend de la classe dérivée :
//     (CellVivante, CellMorte, Obstacle, etc.)

class CellEtat {
    public:

    // Destructeur virtuel
    virtual ~CellEtat() = default;

    // Méthode indiquant si la cellule est vivante.
    // Comportement spécifique selon la sous-classe.
    virtual bool estVivante() const = 0;

    // Méthode indiquant si la cellule est un obstacle.
    // Permet des comportements spéciaux selon les règles du jeu.
    virtual bool estObstacle() const = 0;

};

#endif
