## **Introduction**



Le code fournit est une implémentation en C++ du « Jeu de la vie », un automate cellulaire conceptualisé par John Conway en 1970. Ce jeu nous permet de visualiser l’évolution d’une population de « cellules » à partir de règles simples données.
Notre programme permet de choisir entre deux modes d’affichage :
•	un mode console, qui génère un fichier retraçant l’évolution de chaque génération
•	un mode graphique, basé sur la bibliothèque SFML, offrant une interaction directe avec la grille, la création de motifs et un retour visuel immédiat



L’utilisateur peut initialiser la grille de manière vide et ensuite la remplir, ou bien via un fichier normalisé. Il peut, au travers d’une console, changer les règles et paramètres de la simulation.

D’un point de vu technique, notre programme repose sur les concepts de « Programmation Orientée Objet » (POO). Il est découpé en une multitude de classes qui permettent une lecture et une maintenance simplifiée
Cette documentation présente les différents fichiers, leur fonctionnement général et les interactions clefs entre eux. Cela permet à l’utilisateur de comprendre le fonctionnement interne du programme mais également la manière dont il peut interagir avec celui-ci pour expérimenter dans de bonnes conditions le Jeu de la Vie.



## **Prérequis de compilation et d’exécution :**



##### **Compilateur C++ compatible avec C++17 :**



Le programme utilise un C++ moderne. Nous vous recommandons d’installer un de ces compilateur si vous souhaitez modifier et recompiler le programme :

* GCC >= 7
* Clang >= 5
* MS Visual Studio (2019 ou plus récent)





##### **Bibliothèque SFML :**



Notre programme utilise la bibliothèque SFML pour l’affichage graphique et la musique d’ambiance.
Il vous faudra donc installer SFML 3 ou une version antérieure.
Nous fournissons dans le .zip les DLL nécessaires, mais il vous faudra tout de même installer la bibliothèque.



###### Sous Linux :

Bash : sudo apt install libsfml-dev



###### Sous Windows :

* Créer un dossier simple dans le C:/
* Se placer dans le dossier avec GIT BASH
* Utiliser la suite de commandes : 		git init
  git clone https://github.com/SFML/SFML



#### **Optionnel : Fichier d’initialisation :**



Vous avez la possibilité d’initialiser la grille à partir d’un fichier. Pour se faire, vous devez placer un fichier .txt (et UNIQUEMENT .txt) dans le même dossier que le programme « main.cpp ».
Vous devrez ensuite, lors de l’exécution du programme, écrire le nom du fichier (avec son extension), dans l’entrée console demandée.



Votre fichier .txt doit cependant respecter une normalisation précise imposée :

L H
0 1 0 0 ...
1 1 0 1 ...
…



Avec L = nombre de lignes
Et H = nombre de colonne



D’ailleurs, sachez que si les entrées ne sont pas « complètes » (moins d’entrées que la longueur ou la hauteur rentrée), le programme ignorera simplement les cases non-initialisées et les initialisera automatiquement comme mortes.



##### **Commande de compilation :**



Afin de compiler sans problème, nous vous fournissons une commande de compilation bash à compléter selon votre installation de SFML (cette commande exécute automatiquement le programme à la fin de la compilation) :



“g++ -std=c++17 -Wall -Wextra -g \*.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o game.exe; if ($?) { ./game.exe }”



Si vous présentez des problèmes avec SFML (ce qui est très probable), vous pouvez indiquer les fichiers pour chercher les ressources de la bibliothèque à votre compilateur avec la commande :



“g++ -std=c++17 -Wall -Wextra -g \*.cpp -IC:/ SFML/include -LC:/ SFML-build/lib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -o game.exe; if ($?) { ./game.exe }”



C:/SFML/include est le chemin vers le dossier « include » de votre version de SFML précédemment téléchargée avec git.

C:/SFML-build/lib est le chemin vers le dossier « lib » de votre version de SFML compilée



##### **Exécution :**



Pour exécuter le programme, vous avez simplement à lancer “ game.exe” via un double clic quand le dossier, ou bien à se placer dans le dosser en bash puis lancer la commande :
“ ./game.exe”

