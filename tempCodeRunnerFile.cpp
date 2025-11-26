    cout << "          Bienvenue dans le Jeu de la Vie\n";
    cout << "========================================\n\n";

    while (rep != 1 && rep != 2) {
        cout << "Veuillez choisir votre mode de jeu :\n";
        cout << "  1 - Mode automatique\n";
        cout << "  2 - Nombre predefini de generations\n";
        cout << "Votre choix : ";
        cin >> rep;
        cout << "\n";
    }

    if (rep == 2) {
        cout << "----------------------------------------\n";
        cout << "Combien de generations souhaitez-vous ?\n";
        cout << "Entrez un nombre : ";
        cin >> max_generations;
        cout << "----------------------------------------\n\n";

        Regles.set_max_generations(max_generations);
        Regles.x_generation();
    }

    rep = 3;
    while (rep != 1 && rep != 2) {
        cout << "Veuillez choisir votre mode d'affichage :\n";
        cout << "  1 - Affichage console\n";
        cout << "  2 - Affichage graphique\n";
        cout << "Votre choix : ";
        cin >> rep;
        cout << "\n";
    }

    if (rep == 1) {
        Regles.afficher();
    }

    rep = 3;
    while (rep != 1 && rep != 2) {
        cout << "Veuillez choisir la methode d'initialisation :\n";
        cout << "  1 - Initialisation vide\n";
        cout << "  2 - Initialisation via un fichier\n";
        cout << "Votre choix : ";
        cin >> rep;
        cout << "\n";
    }

    string ligne;
    string filename;

    cout << "Veuillez entrer le nom du fichier (avec extension) :\n";
    cout << "Nom du fichier : ";
    cin >> filename;
