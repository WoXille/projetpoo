#ifndef REGLE_HPP
#define REGLE_HPP

#include <iostream>

class Regle {
private:
    bool graphique = false;
    bool generation = false;
    int max_generations;


public:

    ~Regle()= default;

    void afficher(){graphique = true;};
    void x_generation(){generation = true;};
    bool is_generation(){return generation;};
    void set_max_generations(int max_gen){max_generations = max_gen;};


};

#endif // REGLE_HPP
