#ifndef REGLE_HPP
#define REGLE_HPP

#include <iostream>

class Regle {
private:
    bool graphique = false;
    bool generation = false;
    int max_generations = 0;
    int voisins_max = 3;
    int voisins_min = 2;
    int naissance = 3;

public:

    ~Regle()= default;

    void afficher(){graphique = true;};
    bool is_afficher(){return graphique;};
    void x_generation(){generation = true;};
    bool is_generation(){return generation;};
    void set_max_generations(int max_gen){max_generations = max_gen;};
    int get_max_generations(){return max_generations;};
    void set_rules(int v_max, int v_min, int naiss){voisins_max = v_max; voisins_min = v_min; naissance = naiss;};
    int get_voisins_max(){return voisins_max;};
    int get_voisins_min(){return voisins_min;};
    int get_naissance(){return naissance;};


};

#endif // REGLE_HPP
