/**
 * @file        timer.c
 * @brief       Contient l'implémentation des fonctions de temps, SDL_Delay . . .
 * @author      Meunier Rodrigue Nicolas Lemoult Mathis Morisseau
 * @version     1.0
 * @date        2021
 * @copyright   Le Mans Université
 */
#include "../lib/timer.h"

/**
 * \fn void delay()
 * \brief Cette fonction effectue une pause dans le programme pour faire correpondre les images affichées par le programme aux fps demandées par l'utilisateur (si le joueurs demande 60fps alors le programme ne devra faire une seule boucle par 16ms)
 */
void delay()
{
    struct_jeu.tableau_fps[struct_jeu.frames_evolution%20]=1000/((struct_jeu.ticks_fin-struct_jeu.ticks_depart)?(struct_jeu.ticks_fin-struct_jeu.ticks_depart):1);
    if(struct_jeu.frames_evolution%20)relever_fps();
    struct_jeu.ticks_fin=SDL_GetTicks();

    int difference=struct_jeu.ticks_fin-struct_jeu.ticks_depart;//cette différence correspond au temps qu'a mis le programme � faire une boucle (ex:16ms -> 60FPS)
    if(difference<(1000/jeu_parametres.plageFPS[jeu_parametres.fps]))//si la différence est moins grande (le programme � mis moins de temps que l'�quivalent des fps max alors le programme fait une pause de cette nouvelle diff�rence
        SDL_Delay((1000/jeu_parametres.plageFPS[jeu_parametres.fps])-difference);
    else
        struct_jeu.ticks_depart=struct_jeu.ticks_fin;

    if(struct_jeu.ticks_fin-TICKS_RATE_EVOLUTION>=struct_jeu.ticks_evo)
    {
        struct_jeu.ticks_evo=struct_jeu.ticks_fin;
        struct_jeu.frames_evolution++;
    }
}

/**
 * \fn void relever_fps()
 * \brief Cette fonction relève dans le tableau des fps, le nombre le plus bas, le plus haut et la moyenne. Si le porgramme va "trop vite" la fonction ne sortira pas de nombre plus haut que les fps
 */
void relever_fps()
{
    int compteur=0;
    struct_jeu.fpsMax=0;
    struct_jeu.fpsMin=jeu_parametres.plageFPS[jeu_parametres.fps];
    for(int i=0; i<20; i++)
    {
        if(struct_jeu.tableau_fps[i]>struct_jeu.fpsMax)struct_jeu.fpsMax=struct_jeu.tableau_fps[i];
        if(struct_jeu.tableau_fps[i]<struct_jeu.fpsMin)struct_jeu.fpsMin=struct_jeu.tableau_fps[i];
        struct_jeu.fpsMoy+=struct_jeu.tableau_fps[i];
        compteur++;
    }
    struct_jeu.fpsMoy/=(compteur?compteur:1);
    if(struct_jeu.fpsMax>jeu_parametres.plageFPS[jeu_parametres.fps])struct_jeu.fpsMax=jeu_parametres.plageFPS[jeu_parametres.fps];
    if(struct_jeu.fpsMin>jeu_parametres.plageFPS[jeu_parametres.fps])struct_jeu.fpsMin=jeu_parametres.plageFPS[jeu_parametres.fps];
    if(struct_jeu.fpsMoy>jeu_parametres.plageFPS[jeu_parametres.fps])struct_jeu.fpsMoy=jeu_parametres.plageFPS[jeu_parametres.fps];
}

void action_timer()
{
    if(struct_jeu.ticks_fin-TICKS_RATE_ACTIONS>=struct_jeu.ticks_actions)
    {
        struct_jeu.ticks_actions=struct_jeu.ticks_fin;
        avancer();
        sauter();
        attaquer();
        repos();
        pesanteur();
    }
}

void initialisation_fps()
{
    jeu_parametres.plageFPS[0]=30;
    jeu_parametres.plageFPS[1]=60;
    jeu_parametres.plageFPS[2]=75;
    jeu_parametres.plageFPS[3]=144;
    jeu_parametres.plageFPS[4]=255;
    jeu_parametres.plageFPS[5]=1000;
    struct_jeu.ticks_depart=0;
    struct_jeu.ticks_fin=1;
    struct_jeu.frames_evolution=0;
    memset(struct_jeu.tableau_fps,0,sizeof(int)*20);
}
