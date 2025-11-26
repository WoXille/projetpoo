#ifndef REGLE_HPP
#define REGLE_HPP

#include <iostream>

class Regle {
private:
    bool graphique = false;
    bool generation = false;
    int max_generations;


public:
    Regle(int l, int h);
    ~Regle();

    // Initialisation de la grille
    void afficher(){graphique = true;};
    void x_generation(){generation = true;};


};

#endif // REGLE_HPP
