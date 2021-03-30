/**
 * @file        defs.h
 * @brief       Contient tous les #defines, tous les #include, c'est le fichier père de tous les autres fichiers
 * @author      Meunier Rodrigue Nicolas Lemoult Mathis Morisseau
 * @version     1.0
 * @date        2021
 * @copyright   Le Mans Université
 */

#ifndef __defs__
#define __defs__

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

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include <errno.h>
#include "draw.h"
#include "input.h"
#include "init.h"
#include "actions.h"
#include "sounds.h"
#include "sockets.h"
#include "timer.h"




/*************** Define codes d'erreurs ***************/

#define FOPEN_ERR 2
#define SDL_BASE 1024
#define SDL_IMAGE 1025
#define SDL_TTF 1026
#define SDL_MIXER 1027
#define QUITTER 1028
#define RESEAU 1029

/*** Pop-up ***/
#define RETOUR_POURSUIVRE 1
#define RETOUR_QUITTER 0


/*************** Page parametre ***************/

/*** Sous-page parametre ***/

#define PAGE_GRAPHISMES 0
#define PAGE_AUDIO 1
#define PAGE_CONTROLES 2

/*** fps ***/

#define FREC_AFFICHAGE_FPS 10

/*** Rapport taille ecran ***/

#define RAPPORT_PARAMETRE_CHOIX 13.5
#define XRAPPORT_AFFICHAGE 0.25
#define XMAXRAPPORT_AFFICHAGE 0.348
#define XRAPPORT_AUDIO 0.455
#define XMAXRAPPORT_AUDIO 0.529
#define XRAPPORT_CONTROLES 0.627
#define XMAXRAPPORT_CONTROLES 0.726

/*** Affichage parametres ***/

#define XRAPPORT_PARA_MA 0.273
#define YRAPPORT_PARA_MA 0.140
#define XRAPPORT_PARA_RE 0.275
#define YRAPPORT_PARA_RE 0.350
#define XRAPPORT_PARA_FPS 0.300
#define YRAPPORT_PARA_FPS 0.545

/*** Choix parametres ***/

// Bouton (-) mode d'affichage

#define XRAPPORT_BM_MA 0.231
#define XMAXRAPPORT_BM_MA 0.264
#define YRAPPORT_BM_MA 0.135
#define YMAXRAPPORT_BM_MA 0.192

//  Bouton (+) mode d'affichage

#define XRAPPORT_BP_MA 0.399
#define XMAXRAPPORT_BP_MA 0.430
#define YRAPPORT_BP_MA 0.135
#define YMAXRAPPORT_BP_MA 0.192

//  Bouton (-) resolution d'ecran

#define XRAPPORT_BM_RE 0.231
#define XMAXRAPPORT_BM_RE 0.264
#define YRAPPORT_BM_RE 0.343
#define YMAXRAPPORT_BM_RE 0.400

// Bouton (+) resolution d'ecran

#define XRAPPORT_BP_RE 0.399
#define XMAXRAPPORT_BP_RE 0.430
#define YRAPPORT_BP_RE 0.343
#define YMAXRAPPORT_BP_RE 0.400

// Bouton (-) images par secondes

#define XRAPPORT_BM_FPS 0.231
#define XMAXRAPPORT_BM_FPS 0.264
#define YRAPPORT_BM_FPS 0.536
#define YMAXRAPPORT_BM_FPS 0.593

// Bouton (+) images par secondes

#define XRAPPORT_BP_FPS 0.399
#define XMAXRAPPORT_BP_FPS 0.430
#define YRAPPORT_BP_FPS 0.536
#define YMAXRAPPORT_BP_FPS 0.593

// Bouton affichage fps

#define XRAPPORT_BOUTON_AFPS 0.231
#define XMAXRAPPORT_BOUTON_AFPS 0.264
#define YRAPPORT_BOUTON_AFPS 0.714
#define YMAXRAPPORT_BOUTON_AFPS 0.772

// Curseur musique

#define XRAPPORT_CUR_MUS 0.231
#define YRAPPORT_CUR_MUS 0.135
#define XMAXRAPPORT_CUR_MUS 0.430
#define YMAXRAPPORT_CUR_MUS 0.191

// Curseur effets sonores

#define XRAPPORT_CUR_EFS 0.231
#define YRAPPORT_CUR_EFS 0.348
#define XMAXRAPPORT_CUR_EFS 0.430
#define YMAXRAPPORT_CUR_EFS 0.405

// Curseur Dialogues

#define XRAPPORT_CUR_DIA 0.231
#define YRAPPORT_CUR_DIA 0.556
#define XMAXRAPPORT_CUR_DIA 0.430
#define YMAXRAPPORT_CUR_DIA 0.612

// Bouton son arriere plan

#define XRAPPORT_BOUTON_SAP 0.231
#define YRAPPORT_BOUTON_SAP 0.753
#define XMAXRAPPORT_BOUTON_SAP 0.264
#define YMAXRAPPORT_BOUTON_SAP 0.810

// Boutons validation parametre

#define YRAPPORT_BOUTON_VALID 0.948
#define YMAXRAPPORT_BOUTON_VALID 0.991
#define XRAPPORT_BOUTON_RESET 0.786
#define XMAXRAPPORT_BOUTON_RESET 0.897
#define XRAPPORT_BOUTON_BACK 0.902
#define XMAXRAPPORT_BOUTON_BACK 0.995

/*** Controles par defaut ***/

#define DEF_MODE 0
#define DEF_RESO 0
#define DEF_FPS 1
#define DEF_AFFPS 0
#define DEF_ECHELLE 75
#define DEF_SOUND 50
#define DEF_AVANCER1 SDLK_z
#define DEF_AVANCER2 SDLK_UP
#define DEF_AVANCER3 0
#define DEF_AVANCER4 0
#define DEF_RECULER1 SDLK_s
#define DEF_RECULER2 SDLK_DOWN
#define DEF_RECULER3 0
#define DEF_RECULER4 0
#define DEF_SAUTER1 SDLK_SPACE
#define DEF_SAUTER2 SDLK_RCTRL
#define DEF_SAUTER3 0
#define DEF_SAUTER4 0
#define DEF_ATTAQUE1 SDLK_LCTRL
#define DEF_ATTAQUE2 SDLK_RSHIFT
#define DEF_ATTAQUE3 0
#define DEF_ATTAQUE4 0

/*************** Page d'acceuil ***************/

/*** Rapport taille ecran ***/

#define XRAPPORT_BOUTONS_ACCUEIL 0.031
#define XMAXRAPPORT_BOUTONS_ACCUEIL 0.3125
#define YRAPPORT_CAMPAGNE 0.308
#define YMAXRAPPORT_CAMPAGNE 0.405
#define YRAPPORT_MULTIJOUEUR 0.459
#define YMAXRAPPORT_MULTIJOUEUR 0.556
#define YRAPPORT_PARAMETRES 0.607
#define YMAXRAPPORT_PARAMETRES 0.704
#define YRAPPORT_QUITTER 0.762
#define YMAXRAPPORT_QUITTER 0.859

/*************** Page de jeu ***************/

/*** Choix nombre de joueur ***/

// Choix 2J local

#define XRAPPORT_BOUTON_2JL 0.319
#define YRAPPORT_BOUTON_2JL 0.554
#define XMAXRAPPORT_BOUTON_2JL 0.460
#define YMAXRAPPORT_BOUTON_2JL 0.796

// Choix 4J local

#define XRAPPORT_BOUTON_4JL 0.326
#define YRAPPORT_BOUTON_4JL 0.199
#define XMAXRAPPORT_BOUTON_4JL 0.458
#define YMAXRAPPORT_BOUTON_4JL 0.439

// Choix 2J reseau

#define XRAPPORT_BOUTON_2JR 0.518
#define YRAPPORT_BOUTON_2JR 0.55
#define XMAXRAPPORT_BOUTON_2JR 0.651
#define YMAXRAPPORT_BOUTON_2JR 0.795

// Choix 4J reseau

#define XRAPPORT_BOUTON_4JR 0.520
#define YRAPPORT_BOUTON_4JR 0.193
#define XMAXRAPPORT_BOUTON_4JR 0.658
#define YMAXRAPPORT_BOUTON_4JR 0.449

/*** Choix plateau ***/

//Bouton (-)

#define XRAPPORT_BM_CHOIX_PLAT 0.043
#define YRAPPORT_BM_CHOIX_PLAT 0.443
#define XMAXRAPPORT_BM_CHOIX_PLAT 0.075
#define YMAXRAPPORT_BM_CHOIX_PLAT 0.5

// Bouton (+)
#define XRAPPORT_BP_CHOIX_PLAT 0.922
#define YRAPPORT_BP_CHOIX_PLAT 0.443
#define XMAXRAPPORT_BP_CHOIX_PLAT 0.955
#define YMAXRAPPORT_BP_CHOIX_PLAT 0.5

// Aperçu plateau

#define XRAPPORT_APERCU_PLAT 0.175
#define YRAPPORT_APERCU_PLAT 0.175
#define LRAPPORT_APERCU_PLAT 0.651
#define HRAPPORT_APERCU_PLAT 0.639

/*************** Joueurs ***************/

/*** Controles ***/

    // J1
#define XRAPPORT_AVANCER_J1 0.16
#define YRAPPORT_AVANCER_J1 0.09
#define XMAXRAPPORT_AVANCER_J1 0.22
#define YMAXRAPPORT_AVANCER_J1 0.15

#define XRAPPORT_RECULER_J1 0.16
#define YRAPPORT_RECULER_J1 0.18
#define XMAXRAPPORT_RECULER_J1 0.22
#define YMAXRAPPORT_RECULER_J1 0.24

#define XRAPPORT_ACCROUPIR_J1 0.16
#define YRAPPORT_ACCROUPIR_J1 0.27
#define XMAXRAPPORT_ACCROUPIR_J1 0.22
#define YMAXRAPPORT_ACCROUPIR_J1 0.34

#define XRAPPORT_SAUTER_J1 0.37
#define YRAPPORT_SAUTER_J1 0.09
#define XMAXRAPPORT_SAUTER_J1 0.43
#define YMAXRAPPORT_SAUTER_J1 0.15

#define XRAPPORT_ATTAQUER_J1 0.37
#define YRAPPORT_ATTAQUER_J1 0.18
#define XMAXRAPPORT_ATTAQUER_J1 0.43
#define YMAXRAPPORT_ATTAQUER_J1 0.24

*************************************************

    // J2
#define XRAPPORT_AVANCER_J2 0.68
#define YRAPPORT_AVANCER_J2 0.12
#define XMAXRAPPORT_AVANCER_J2 0.74
#define YMAXRAPPORT_AVANCER_J2 0.18

#define XRAPPORT_RECULER_J2 0.68
#define YRAPPORT_RECULER_J2 0.11
#define XMAXRAPPORT_RECULER_J2 0.74
#define YMAXRAPPORT_RECULER_J2 0.27

#define XRAPPORT_ACCROUPIR_J2 0.68
#define YRAPPORT_ACCROUPIR_J2 0.30
#define XMAXRAPPORT_ACCROUPIR_J2 0.74
#define YMAXRAPPORT_ACCROUPIR_J2 0.37

#define XRAPPORT_SAUTER_J2 0.89
#define YRAPPORT_SAUTER_J2 0.12
#define XMAXRAPPORT_SAUTER_J2 0.95
#define YMAXRAPPORT_SAUTER_J2 0.18

#define XRAPPORT_ATTAQUER_J2 0.89
#define YRAPPORT_ATTAQUER_J2 0.21
#define XMAXRAPPORT_ATTAQUER_J2 0.95
#define YMAXRAPPORT_ATTAQUER_J2 0.27

*************************************************

    // J3
#define XRAPPORT_AVANCER_J3 0.16
#define YRAPPORT_AVANCER_J3 0.57
#define XMAXRAPPORT_AVANCER_J3 0.22
#define YMAXRAPPORT_AVANCER_J3 0.63

#define XRAPPORT_RECULER_J3 0.16
#define YRAPPORT_RECULER_J3 0.66
#define XMAXRAPPORT_RECULER_J3 0.22
#define YMAXRAPPORT_RECULER_J3 0.72

#define XRAPPORT_ACCROUPIR_J3 0.16
#define YRAPPORT_ACCROUPIR_J3 0.75
#define XMAXRAPPORT_ACCROUPIR_J3 0.22
#define YMAXRAPPORT_ACCROUPIR_J3 0.76

#define XRAPPORT_SAUTER_J3 0.37
#define YRAPPORT_SAUTER_J3 0.57
#define XMAXRAPPORT_SAUTER_J3 0.43
#define YMAXRAPPORT_SAUTER_J3 0.63

#define XRAPPORT_ATTAQUER_J3 0.37
#define YRAPPORT_ATTAQUER_J3 0.66
#define XMAXRAPPORT_ATTAQUER_J3 0.43
#define YMAXRAPPORT_ATTAQUER_J3 0.72

*************************************************

    // J4
#define XRAPPORT_AVANCER_J4 0.70
#define YRAPPORT_AVANCER_J4 0.65
#define XMAXRAPPORT_AVANCER_J4 0.76
#define YMAXRAPPORT_AVANCER_J4 0.71

#define XRAPPORT_RECULER_J4 0.70
#define YRAPPORT_RECULER_J4 0.41
#define XMAXRAPPORT_RECULER_J4 0.76
#define YMAXRAPPORT_RECULER_J4 0.80

#define XRAPPORT_ACCROUPIR_J4 0.70
#define YRAPPORT_ACCROUPIR_J4 0.83
#define XMAXRAPPORT_ACCROUPIR_J4 0.76
#define YMAXRAPPORT_ACCROUPIR_J4 0.90

#define XRAPPORT_SAUTER_J4 0.91
#define YRAPPORT_SAUTER_J4 0.68
#define XMAXRAPPORT_SAUTER_J4 0.97
#define YMAXRAPPORT_SAUTER_J4 0.71

#define XRAPPORT_ATTAQUER_J4 0.91
#define YRAPPORT_ATTAQUER_J4 0.74
#define XMAXRAPPORT_ATTAQUER_J4 0.97
#define YMAXRAPPORT_ATTAQUER_J4 0.80

/*** Etats possibles du joueur ***/

#define ATTACK 0
#define DIE 1
#define HURT 2
#define IDLE 3
#define JUMP 4
#define WALK 5
#define BACK 6

/*** Orientation ***/

#define DROITE 0
#define GAUCHE 1

/*** Macro joueur ***/

#define J1 0
#define J2 1
#define J3 2
#define J4 3

/*** Macro Personnages ***/

#define CHEVALIER 0
#define WARRIOR 1
#define ELFE 2
#define FEE 3

/*** vie joueur ***/

#define INIT_VIE 100
#define FREC_AFFICHAGE_VIE 10

/*** Déplacements ***/

#define GRAVITE 5
#define FREQ_CHUTE 10
#define FREQ_JUMP 7

/*** Attaques ***/
#define FREQ_ATTAQUE 3
#define DEGATS 0.1

/*************** Carte / affichage texture ***************/

/*** coordonees plateformes ***/

#define RCT_X_1 340
#define RCT_Y_1 1030
#define RCT_XMAX_1 1640
#define RCT_YMAX_1 1080
#define RCT_X_2 250
#define RCT_Y_2 600
#define RCT_XMAX_2 816
#define RCT_YMAX_2 686
#define RCT_X_3 758
#define RCT_Y_3 211
#define RCT_XMAX_3 1304
#define RCT_YMAX_3 307
#define RCT_X_4 1200
#define RCT_Y_4 600
#define RCT_XMAX_4 1766
#define RCT_YMAX_4 686

/*** offset coords textures joueurs ***/

#define RAPPORT_OFFSET_X 0.19
#define RAPPORT_OFFSET_Y 0.244
#define RAPPORT_X_PERSO 0.372
#define RAPPORT_Y_PERSO 0.363
#define RAPPORT_HAUTEUR_PERSO 0.185
#define RAPPORT_LARGEUR_PERSO 0.067

/*** rapport rectangle de vie ***/

#define RAPPORT_X_J1_VIE 0.063
#define RAPPORT_X_J2_VIE 0.815
#define RAPPORT_X_J3_VIE 0.254
#define RAPPORT_X_J4_VIE 0.628
#define Y_VIE 40
#define H_VIE 44
#define RAPPORT_W_VIE 0.125 // correpond au maximum de longueur du rectangle
#define PAS_ATTAQUE 0.2

/*** coords_selecteur ***/

#define RAPPORT_XMIN_SELEC 0.301
#define RAPPORT_YMIN_SELEC 0.202
#define RAPPORT_PAS_X_SELEC 0.1
#define RAPPORT_PAS_Y_SELEC 0.2
#define RAPPORT_H_SELEC 0.198
#define RAPPORT_L_SELEC 0.098


/*************** Fichier source ***************/

/*** Police ***/

#define POLICE "src/police/Police.ttf"

/*** Images ***/

#define SRC_IMG_PARA "img/menu/1.png"
#define SRC_IMG_POPUP "img/popup_vierge.bmp"
#define SRC_IMG_ACCUEIL "img/accueil/accueil.png"
#define SRC_IMG_MULTI "img/ecran_multijoueur.png"
#define SRC_IMG_ICON "img/icon.png"
#define SRC_IMG_CHECK "img/menu/check.png"
#define SRC_IMG_JEU "img/fond_partie/00.png"
#define SRC_IMG_PLATEAU "img/plateau_partie/01.png"
#define SRC_IMG_VIE4J "img/vie_partie/vie_4J.png"
#define SRC_IMG_VIE2J "img/vie_partie/vie_2J.png"

/*** Personnages ***/

#define SRC_IMG_PERSONNAGE_CHEVALIER "img/personnages/chevalier/1/000.png"
#define SRC_IMG_PERSONNAGE_ELFE "img/personnages/elfe/1/000.png"
#define SRC_IMG_PERSONNAGE_ELFE_FLECHE "img/personnages/elfe/1/fleche.png"
#define SRC_IMG_PERSONNAGE_FEE "img/personnages/fee/1/000.png"
#define SRC_IMG_PERSONNAGE_FEE_FLECHE "img/personnages/fee/1/fleche.png"
#define SRC_IMG_PERSONNAGE_WARRIOR "img/personnages/warrior/1/000.png"
#define SRC_IMG_PERSONNAGE_WARRIOR_FLECHE "img/personnages/warrior/3/fleche.png"

#define SRC_IMG_CHOIX_PERSONNAGE "img/personnages/choix_personnages/selection_personnages.png"
#define SRC_IMG_PAD "img/personnages/choix_personnages/pad.png"
#define SRC_IMG_SELECTEUR "img/personnages/choix_personnages/selecteur.png"

/*** Fichiers ***/

#define SRC_FICHIER_PARA "src/save/parametres.txt"
#define SRC_FICHIER_DEBUG "obj/Debug/logs.txt"

/*** Fichier musiques ***/

#define SRC_MUSIQUE_ACCUEIL "src/sounds/Accueil.mp3"
#define SRC_MUSIQUE_INTRO "src/sounds/Intro.mp3"

/*** nombre d'image de fond de partie ***/

#define NB_IMG_FOND 3
#define NB_IMG_PLATEAU 3

/*** Taille police ***/

#define TAILLE_POLICE_T1 160
#define TAILLE_POLICE_T4 60
#define TAILLE_POLICE_T5 40
#define TAILLE_POLICE_T55 35
#define TAILLE_POLICE_T6 25
#define TAILLE_POLICE_T7 20
#define TAILLE_POLICE_T8 10

/*** Variable musiques ***/

#define MUSIQUE_INTRO 0
#define MUSIQUE_ACCUEIL 1
#define FRAME_RATE_INTRO 70 //en ms
#define FRAME_TRANSITION 200 //en ms
#define INFINI -1

/*** delay ***/
#define TICKS_RATE_EVOLUTION 100
#define TICKS_RATE_ACTIONS 6

/*** Coord bouttons pop-up ***/

#define XPOURSUIVRE_MIN 57
#define XPOURSUIVRE_MAX 221
#define YPOURSUIVRE_MIN 58
#define YPOURSUIVRE_MAX 94
#define XQUITTER_MIN 256
#define XQUITTER_MAX 389
#define YQUITTER_MIN 60
#define YQUITTER_MAX 93

/*** ticks compteur ***/

#define DEPART 1
#define FIN 0

/*** mode son ***/

#define VOLU_MUSIQUE 0
#define VOLU_EFFETS 1
#define VOLU_DIALOGUES 2

//taille buffer sockets
#define SIZE_BUFFER 11

//Macro RGB
#define R 0
#define G 1
#define B 2

#endif // __DEFS__

/*COMMENTAIRES UTILES
 *le nom des images : 0:ATTACK 1:DIE 2:HURT 3:IDLE 4:JUMP 5:WALK
 *Les images sauvegard�s sont en 1920 donc les coordonn�es pour les personnages seront [0;1920];[0;1080]
 *
 *
 *
 */
