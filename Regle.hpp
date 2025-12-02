#ifndef REGLE_HPP
#define REGLE_HPP

#include <iostream>

// Classe permettant de définir les paramètres du Jeu de la Vie.
//
// Elle gère :
//  - les règles de survie et de naissance des cellules (paramétrables)
//  - le mode d'affichage (graphique ou fichier)
//  - la gestion du nombre maximum de générations
class Regle {
private:
    bool graphique = false;    // Indique si l'affichage graphique doit être utilisé
    bool generation = false;   // Active un nombre limité de générations
    int max_generations = 0;   // Nombre maximum de générations (si generation = true)

    // Paramètres des règles du jeu :
    // voisins_max : seuil au-delà duquel une cellule vivante meurt (surpopulation)
    // voisins_min : seuil en-dessous duquel une cellule vivante meurt (isolement)
    // naissance   : nombre exact de voisins vivants nécessaires pour qu'une cellule morte naisse
    int voisins_max = 3;
    int voisins_min = 2;
    int naissance = 3;

public:

    ~Regle()= default;

    // Active le mode graphique.
    void afficher(){ graphique = true; };

    // Retourne vrai si le jeu doit s'afficher graphiquement.
    bool is_afficher(){ return graphique; };

    // Active le mode de génération limitée.
    void x_generation(){ generation = true; };

    // Retourne vrai si le nombre de générations est limité.
    bool is_generation(){ return generation; };

    // Définit le nombre maximum de générations autorisées.
    void set_max_generations(int max_gen){ max_generations = max_gen; };

    // Retourne le nombre maximum de générations paramétré.
    int get_max_generations(){ return max_generations; };

    // Modifie les règles de survie et de naissance.
    // v_max : voisins_max
    // v_min : voisins_min
    // naiss : naissance
    void set_rules(int v_max, int v_min, int naiss){
        voisins_max = v_max;
        voisins_min = v_min;
        naissance = naiss;
    };

    // Accesseurs pour récupérer les paramètres des règles actuelles.
    int get_voisins_max(){ return voisins_max; };
    int get_voisins_min(){ return voisins_min; };
    int get_naissance(){ return naissance; };

};

#endif // REGLE_HPP
