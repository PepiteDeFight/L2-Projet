# Pepite de Fight
## Projet de 2ème année de licence d'informatique

Pepite de Fight est un projet réalisé avec 3 collaborateurs à savoir:
    -Rodrigue Meunier
    -Nicolas Lemoult
    -Mathis Morisseau

Il a été développé dans le cadre du module "Conduite de projet 174UP02" intégrant 3 sous modules:
    -Outils de développement 174UP02A
    -Communication 174UP02B
    -Projet 174UP02C
*********************
*********************
## C'est quoi ? 
    
Pepite de Fight (PDF) est un jeu similaire à la licence de nintendo : Super Smash Bros.
Il incarne les principes simples du jeu, c'est à dire le combat 2 contre 2 ou 4 contre 4.
Petite particularité de notre jeu, il est doté d'un système de réseau lui permettant de jouer en réseau local; Cela est utile dans le cas où vous n'avez que des écrans petits. 
Avec ces nombreux paramètres modifiable, PDF est un jeu assez portable. Il est possible de jouer sur un grand nombre de machine Linux et Windows. 

*********************
*********************
## Status 
Ce tableau représente l'état d'avancement global du projet. En effet le projet n'est pas encore terminé.
|               | Sprites   | Hors jeu            | Jeu                                         | Tests | Total |
| ------------- | ----------| ------------------- | ------------------------------------------- | ----- | ----- |
| Développement | 100%      | 87%                 | 55%                                         | 100%  | 78%   |
| A faire       |           | Selection des fonds | Physique, dégats et fin de partie, campagne |       |       |

Le temps nous étant compté, nous aurons pas le temps de faire tout ce qui était prévu.
En particulité, nous laissons de coté la séction campagne qui ne sera pas réalisé avant la soutenance.
*********************
*********************
## Installation

Partie de nicolas pour l'installation
*********************
*********************
## Development
Nous avons décidé d'organiser les fonctions dans différents fichiers permettant de repérer chaque fonctions dans chaque fichiers. 
Sur ce lien vous pouvez voir un schema représentant l'organisation des fichiers:
![Inclusions des fichiers](https://github.com/PepiteDeFight/L2-Projet/blob/main/img/liens_entre_les_fichiers.png)

Maintenant une bref présentation de chaque module (groupe de fonctions).
Pour commencer, vous pouvez voir que tous les fichiers.c sauf le main incluent leur equivalent en ".h", chaque ".h" incluent struct.h qui est le fichier des structures globales. Et pour finir struct.h inclue defs.h qui est le fichier "maitre" qui possède toutes les déclarations et les définitions permettant à chaque fichiers d'accéder à n'importe quelles fonctions.

### defs.h
    Ce fichier comme indiqué précedement contient l'ensemble des inclusions.
On peut retrouver toutes les librairies externes incluses comme:
    - [SDL.h](https://github.com/PepiteDeFight/L2-Projet/blob/main/SDL/include/SDL.h)
    - [SDL_image](https://github.com/PepiteDeFight/L2-Projet/blob/main/SDL/include/SDL.h)
    - [SDL_ttf](https://github.com/PepiteDeFight/L2-Projet/blob/main/SDL/include/SDL.h)
    - [SDL_Mixer.h](https://github.com/PepiteDeFight/L2-Projet/blob/main/SDL/include/SDL.h)
Il contient également les définitions permettant une meilleure clartée de code.
Petite particularité pour ce [fichier](https://github.com/PepiteDeFight/L2-Projet/blob/main/lib/defs.h) il possède une commande de préprocesseur de plus par rapport aux autres, c'est-à-dire :

    #ifdef _WIN32
    #include <winsock2.h>
    #include <winsock.h>
    #include <windows.h>
    #else
    #include <netdb.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #endif
Cela permet une flexibilité du code, avec ces commandes on peut compiler le code sur windows et sur linux sans devoir changer quoi que ce soit.

*********************
*********************
## Divers

- Makefile intégré
- Développé avec Code::block
- Images libres de droits
- [Gant](https://docs.google.com/spreadsheets/d/1ipVHrZPP3kiP_FIxAHCDkyyDFsxZtWTpcSuICjUDaMI/edit#gid=0) 
- Code déjà compilé sous [github](https://github.com/PepiteDeFight/L2-Projet)


Ce projet est pour nous une grande réussite. Il est le fruit d'un travail acharné et méthodique.
> “La vie, c’est comme une bicyclette,
> il faut avancer pour ne pas perdre l’équilibre.”
> A.Einstein

Nous souhaitons remercier l'ensemble du personnel enseignant pour nous 
avoir aider dans ce projet.
Nous remercions aussi Antoine M. pour nous avoir fait un logo à notre effigie.
*********************
*********************
## License

Tous les fichiers de PDF sont sous aucune licence, les images, sons, polices peuvent être modifié sans pour autant perdre la jouabilité.
Nous réservons aucun droits sur le projet vous pouvez le modifier comme bon vous semble.

**Créer, partager et surtout coder !**
