#ifndef REGLE_HPP
#define REGLE_HPP

#include <iostream>

class Regle {
private:
    bool graphique = false;
    bool generation = false;
    int max_generations = 0;


public:

    ~Regle()= default;

    void afficher(){graphique = true;};
    bool is_afficher(){return graphique;};
    void x_generation(){generation = true;};
    bool is_generation(){return generation;};
    void set_max_generations(int max_gen){max_generations = max_gen;};
    int get_max_generations(){return max_generations;};


};

#endif // REGLE_HPP
