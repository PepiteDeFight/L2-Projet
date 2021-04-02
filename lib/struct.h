/**
 * @file        struct.h
 * @brief       C'est également un fichier père car struct.h contient toutes les déclarations des structures liées au jeu et aux paramètres
 * @author      Meunier Rodrigue Nicolas Lemoult Mathis Morisseau
 * @version     1.0
 * @date        2021
 * @copyright   Le Mans Université
 */
#ifndef __STRUCT__
#define __STRUCT__

#include "defs.h"

/*  STRUCTURES  */

/**
 * \struct t_joueur
 * \brief Objet liés aux informations d'un joueur
 *
 * t_joueur est une structure qui contient toutes
 * les informations nécéssaires d'un joueur
 * pour le bon déroulement d'une partie.
 * Ex: sa vie, sa position, sa direction ...
 */
typedef struct s_joueur
{
    int vie;
    int type_personnage;
    int etat;//idle ,walk ,...
    int evolution;
    int direction;
    float positionX;
    float positionY;
    int modification;
    int jump;
    int coords_objets[2];
    int fleche_dispo;
    SDL_Texture *fleche;
} t_joueur;

/**
 * \struct t_parametres
 * \brief Structure clé du jeu
 *
 * t_parametres est une structure unique déclarée en global,
 * elle est très importante car elle stocke tous les
 * parametres d'un client, comme les controles, la résolution
 * etc . . .
 */
typedef struct
{
    //GRAPHISMES
    int mode;//0 fenetre - 1 Plein Ecran
    int resolution;//variable "compteur" qui d�termine la r�solution � choisir parmi la liste (voir tableau de r�solution)
    int fps;// les fps (30/60/75/144/255/1000)
    int affichFPS;//1 afficher les fps - 0 non
    int plageFPS[6];
    int reso[2][10];

    //INTERFACE
    int echelle;//la "taille" de l'interface 0->100%

    //AUDIO
    int musique;//volume musique 0->100%
    int effets;//volume effets sonores 0->100%
    int dialogues;//volume dialogue 0->100%
    int arriere_plan;//oui ou non
    Mix_Chunk *musiques[10];


    //C-O-N-T-R-O-L-E-S
    int controles[4][4];
    /* J1 : Avancer - reculer - sauter - attaquer
     * J2 : Avancer - reculer - sauter - attaquer
     * J3 : Avancer - reculer - sauter - attaquer
     * J4 : Avancer - reculer - sauter - attaquer
     */

    //T-E-X-U-R-E-S
    SDL_Texture *tabMenu[3];
    //menu
    int page;
} t_parametres;

/**
 * \struct t_gestion
 * \brief Tout comme t_parametres, t_gestion est déclaré une seule fois
 *
 *
 * t_gestion est une structure très importante car elle stocke globalement
 * des pointeurs de structures SDL qui permettent de "garder" des textures.
 * Elle stocke également des informations qui ne sont pas des parametres
 * comme le nombre de joueurs d'une parie, les fps "affichés" etc
 *
 */
typedef struct
{
    /*  PARTIE GRAPHIQUE    */
    SDL_Window *fenetre_jeu;
    SDL_Renderer *rendu_fenetre;
    int choix_resolution;
    SDL_Texture *texture_accueil;
    SDL_Texture *texture_multijoueur;
    SDL_Texture *textures_fond_accueil[100];
    SDL_Texture *transition;
    int frequence_video;
    TTF_Font *police;
    int fpsMoy;
    int fpsMax;
    int fpsMin;
    int tableau_fps[20];
    int focus_loose;

    //texture jeu
    SDL_Texture *textures_fond_jeu[NB_IMG_FOND];
    SDL_Texture *textures_plateau_jeu[NB_IMG_PLATEAU];
    int texture_plateau_jeu_selectione;
    SDL_Texture *textures_personnages_joueurs[4][6][10];
    //menu choix personnages
    SDL_Texture *selection_personnages;
    SDL_Texture *selecteur;

    //fps
    SDL_Surface *surface_fps;
    SDL_Texture *texture_fps;

    //vie joueurs
    SDL_Texture *vie_joueurs;
    SDL_Surface *rectangle_vie;
    SDL_Texture *texture_rect_vie;
    int perte_vie;
    /*-----------------------------*/

    /*  PARTIE JEU      */
    int frames_evolution;
    int nombre_joueurs;
    int reseauOn;
    t_joueur joueurs[4];
    int tableau_event[4][4];

    /*  PARTIE DELAY    */
    int ticks_depart;
    int ticks_fin;
    int ticks_evo;
    int ticks_actions;

    /* DEBUG */
    FILE *debug;

} t_gestion;

typedef struct
{
    int socket_client;
    int socket_serveur;
    struct sockaddr_in adresse_client;//Un client qui se connecte
    struct sockaddr_in adresse_serveur;//Je suis serveur
    int mon_address_longueur;
    char buffer[SIZE_BUFFER];

} t_reseau;

/*  Déclaration des structures en global    */
t_parametres jeu_parametres;
t_gestion struct_jeu;
t_reseau sockets;






#endif // __STRUCT__
