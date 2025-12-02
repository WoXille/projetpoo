#include "game.hpp"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Constructeur : initialise la grille avec la largeur et la hauteur données,
// puis appelle la méthode init() pour charger les ressources (polices, musique, etc.).
Game::Game(int largeur, int hauteur)
    : grille(largeur, hauteur) {
    init();
}

// Destructeur
Game::~Game() {
}

// Initialisation des ressources graphiques et audio du jeu.
// Chargement des polices, de la musique, et initialisation de la grille.
void Game::init() {
    if (!Roboto.openFromFile("assets/fonts/Roboto-Bold.ttf")) {
        cerr << "Erreur : impossible de charger Roboto-Bold.ttf" << endl;
        return;
    }
    if (!Cherolina.openFromFile("assets/fonts/Cherolina.ttf")) {
        cerr << "Erreur : impossible de charger Cherolina.ttf" << endl;
        return;
    }
    if (!AstonScript.openFromFile("assets/fonts/AstonScript.ttf")) {
        cerr << "Erreur : impossible de charger AstonScript.ttf" << endl;
        return;
    }
    if (!music.openFromFile("assets/music/kahoot_music.ogg")) { 
        std::cerr << "Erreur lors du chargement de la musique." << std::endl;
        return;
    }
    // La musique tourne en boucle et le volume est positionné.
    music.setLooping(true);
    music.setVolume(100.f); // au cas où

    // Initialisation des cellules de la grille
    grille.init();
}



// Effectue une itération du Jeu de la Vie en deux passes :
// 1) calcul du nombre de voisins vivants pour chaque cellule (sauf obstacles)
// 2) application des règles de naissance/survie/mort selon l'objet Regle.
void Game::runIteration(Regle * Regles) {
    int tempTab[100][100];

    // Première passe : calcul et stockage du nombre de voisins vivants.
    for (int i = 0; i < grille.getLargeur(); ++i) {
        for (int j = 0; j < grille.getHauteur(); ++j) {
            Cell* cell = grille.getCell(i, j);
            if (cell->estObstacle()) {
                // Valeur spéciale pour marquer les obstacles et les ignorer ensuite.
                tempTab[i][j] = -1;
                continue;
            }
            else {
                tempTab[i][j] = grille.iteration(cell);
            }
        }
    }

    // Deuxième passe : application des règles du jeu à partir de tempTab.
    for (int i = 0; i < grille.getLargeur(); ++i) {
        for (int j = 0; j < grille.getHauteur(); ++j) {
            Cell* cell = grille.getCell(i, j);
            int voisinsVivants = tempTab[i][j];

            // Les cellules marquées comme obstacles sont ignorées.
            if (voisinsVivants == -1) {
                continue;
            }
            // Règle de naissance : une cellule morte devient vivante
            // si elle a exactement le nombre de voisins défini par les règles.
            else if (!(cell->estVivante()) && voisinsVivants == Regles->get_naissance()) {
                cell->RendreVivante();
            }
            // Règle de mort : une cellule vivante meurt si elle a trop peu ou trop de voisins.
            else if (cell->estVivante() &&
                     (voisinsVivants < Regles->get_voisins_min() ||
                      voisinsVivants > Regles->get_voisins_max())) {
                cell->RendreMorte();
            }
        }
    }
}

// Écrit l'état courant de la grille dans un fichier texte.
// Chaque cellule est représentée par 1 (vivante) ou 0 (morte), génération par génération.
void Game::display(int generation, std::string filename) const {
    ofstream fichier(filename, ios::app);
    if (!fichier.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier " << filename << endl;
        return;
    }

    // En-tête indiquant le numéro de génération.
    fichier << "Generation :" << generation << endl;

    // Parcours de la grille ligne par ligne.
    for (int j = 0; j < grille.getHauteur(); ++j) {
        for (int i = 0; i < grille.getLargeur(); ++i) {
            Cell* cell = grille.getCell(i, j);
            if (cell->estVivante()) {
                fichier << "1 ";
            } else {
                fichier << "0 ";
            }
        }
        fichier << endl;
    }

    // Ligne vide entre deux générations pour faciliter la lecture (et conforme au format demandé dans le sujet).
    fichier << endl;
    fichier.close();
}

// Accès direct à une cellule via les coordonnées (x, y).
Cell* Game::getCell(int x, int y) const {
    return grille.getCell(x, y);
}

// Affiche la grille et l'interface d'information dans la fenêtre SFML.
// Gère également l'aperçu des motifs en fonction du mode et de la position de la souris.
// (Moteur graphique principal)
void Game::renderGrid(sf::RenderWindow& window, int CellSize) {
    int endgrid = CellSize * grille.getLargeur();
    window.clear();

    // Récupération de la position de la souris dans la fenêtre.
    sf::Vector2i pos = sf::Mouse::getPosition(window);

    // Bandeau de titre à droite de la grille.
    sf::RectangleShape titleBackground(sf::Vector2f(600.f, 100.f));
    titleBackground.setFillColor(sf::Color (140,0,0));
    titleBackground.setPosition(sf::Vector2f(endgrid, 0.f));

    // Titre principal "Game of Life".
    sf::Text textmain(AstonScript, "Game of Life", 35);
    textmain.setFillColor(sf::Color::White);
    textmain.setPosition(sf::Vector2f(endgrid + 125, 30.f));

    // Hauteur de la zone d'information (au moins 600 pixels).
    int hauteurgrid;
    if (CellSize * grille.getHauteur() < 600) {
        hauteurgrid = 600;
    } else {
        hauteurgrid = CellSize * grille.getHauteur();
    }

    // Fond pour la zone d'informations (instructions, mode, etc.).
    sf::RectangleShape infobackground(sf::Vector2f(600.f, hauteurgrid - 100.f));
    infobackground.setFillColor(sf::Color (150,150,150));
    infobackground.setPosition(sf::Vector2f(endgrid, 100.f));
    
    // Nom du mode courant en fonction de la valeur de 'mode'.
    string modenom;
    if (getMode() == 0) {
        modenom = "NORMAL";
    } else if (getMode() == 1) {
        modenom = "GLIDER";
    } else if (getMode() == 2) {
        modenom = "HELICOPTER";
    } else if (getMode() == 3) {
        modenom = "OBSTACLE";
    }

    // Texte d'aide affichant le mode actuel et les raccourcis clavier.
    string txtinfo = " MODE ACTUEL : " + modenom + "\n\n PAUSE = ESPACE\n\n PLAY = ENTER\n\n Rendre Vivante = Clic Gauche\n\n Rendre Morte = Clic Droit\n\n Clear la grille = C\n\n Mode Normal = N\n\n Mode Glider = G\n\n Mode Helicopter = H\n\n Mode Obstacle = O\n\n Play Musique = P\n\n Stop Musique = M";

    sf::Text textinfo(Roboto, txtinfo, 24);
    textinfo.setFillColor(sf::Color::White);
    textinfo.setPosition(sf::Vector2f(endgrid + 20, 110.f));
    
    // Forme de base utilisée pour dessiner chaque cellule.
    sf::RectangleShape cellShape(sf::Vector2f(CellSize - 1.0f, CellSize - 1.0f));

    // Lambda pour surligner une cellule en rouge (prévisualisation).
    auto rendrerouge = [&](int x, int y) {
        cellShape.setPosition(sf::Vector2f(
            static_cast<float>(x * CellSize),
            static_cast<float>(y * CellSize)
        ));
        cellShape.setFillColor(sf::Color(255, 0, 0, 100)); // Rouge semi-transparent
        window.draw(cellShape);
    };

    // Lambda pour surligner une cellule en bleu (prévisualisation obstacle).
    auto rendrebleu = [&](int x, int y) {
        cellShape.setPosition(sf::Vector2f(
            static_cast<float>(x * CellSize),
            static_cast<float>(y * CellSize)
        ));
        cellShape.setFillColor(sf::Color(0, 0, 255, 100)); // Bleu semi-transparent
        window.draw(cellShape);
    };

    // Parcours de toutes les cellules de la grille pour les afficher.
    for (int x = 0; x < grille.getLargeur(); ++x) {
        for (int y = 0; y < grille.getHauteur(); ++y) {

            // Cas des cellules vivantes.
            if (grille.getCell(x, y)->estVivante()) {
                cellShape.setPosition(sf::Vector2f(
                    static_cast<float>(x * CellSize),
                    static_cast<float>(y * CellSize)));
                if (grille.getCell(x, y)->estObstacle()) {
                    // Cellule vivante obstacle : couleur distincte.
                    cellShape.setFillColor(sf::Color (200,200,255));
                } else {
                    // Cellule vivante normale.
                    cellShape.setFillColor(sf::Color::White);
                }
                window.draw(cellShape);
            }
            // Cas des cellules mortes.
            else {
                if (grille.getCell(x, y)->estObstacle()) {
                    // Cellule morte obstacle : autre couleur.
                    cellShape.setPosition(sf::Vector2f(
                        static_cast<float>(x * CellSize),
                        static_cast<float>(y * CellSize)));
                    cellShape.setFillColor(sf::Color (0,0,100));
                    window.draw(cellShape);
                }
            }
            
            // Prévisualisation en fonction du mode et de la position de la souris.

            // Mode OBSTACLE : surlignage en bleu de la cellule sous la souris.
            if (pos.x / CellSize == x && pos.y / CellSize == y && getMode() == 3) {
                rendrebleu(x, y);
            }

            // Mode NORMAL : surlignage en rouge de la cellule sous la souris.
            if (pos.x / CellSize == x && pos.y / CellSize == y && getMode() == 0) {
                rendrerouge(x, y);
            }

            // Mode GLIDER : surlignage de la forme d'un planeur autour de la cellule.
            if (pos.x / CellSize == x && pos.y / CellSize == y && getMode() == 1) {
                rendrerouge(x+1, y+1);
                rendrerouge(x+1, y);
                rendrerouge(x+1, y-1);
                rendrerouge(x-1, y);
                rendrerouge(x, y-1);
            }

            // Mode HELICOPTER : surlignage d'un motif spécifique.
            if (pos.x / CellSize == x && pos.y / CellSize == y && getMode() == 2) {
                rendrerouge(x, y);
                rendrerouge(x, y+1);
                rendrerouge(x, y-1);
            }
        }
    }

    // Dessin des éléments d'interface à droite de la grille.
    window.draw(titleBackground);
    window.draw(textmain);
    window.draw(infobackground);
    window.draw(textinfo);

    // Affichage final du frame.
    window.display();
}
