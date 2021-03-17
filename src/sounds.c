/**
 * @file        sounds.c
 * @brief       Contient l'implémentation des fonctions en rapport avec la musique, la création des channels, le changement de volume etc
 * @author      Meunier Rodrigue Nicolas Lemoult Mathis Morisseau
 * @version     1.0
 * @date        2021
 * @copyright   Le Mans Université
 */
#include "../include/sounds.h"


/**
 * \fn void creation_canaux_musique()
 * \brief Cette fonction alloue des canaux de musiques pour pouvoir mettre plusieurs sons en même temps comme les effets des joueurs ma ùusique d'ambiance etc . . .
 */
void creation_canaux_musique()
{
    if(Mix_AllocateChannels(7) == -1)quitter(SDL_MIXER);
    /*Cannaux:
     *0:Musique fond
     *1:Effets joueur 1
     *2:Effets Joueur 2
     *3:Effets Joueur 3
     *4:Effets Joueur 4
     *5:Dialogues
     *6:Buffer
     */
    jeu_parametres.musiques[MUSIQUE_INTRO]=Mix_LoadWAV(SRC_MUSIQUE_INTRO);
    jeu_parametres.musiques[MUSIQUE_ACCUEIL]=Mix_LoadWAV(SRC_MUSIQUE_ACCUEIL);
}

/**
 * \fn void chargement_musique(int channel, int extra,int rep)
 * \brief Cette fonction permet de jouer une musique
 * \param channel Correspond au cannal de musique (0->6)
 * \param extra Indice dans le tableau jeu_parametres.musiques[] correspondant à la musique voulu
 * \param rep Correspond au nombre de répétitions (-1 -> infini)
 */
void chargement_musique(int channel, int extra,int rep)
{
    Mix_PlayChannel(channel, jeu_parametres.musiques[extra], rep);
}

/**
 * \fn void changement_volumes_musiques()
 * \brief Cette fonction permet de changer les volumes des canaux de musiques
 */
void changement_volumes_musiques()
{
    if(struct_jeu.focus_loose && !jeu_parametres.arriere_plan) //si on est sorti de l'�cran et que l'utilisateur a choisi de retirer le son
    {
        for(int i=0; i<7; i++)
            if(Mix_Volume(i,0) == -1)quitter(SDL_MIXER);
    }
    else
    {
        if(Mix_Volume(0, jeu_parametres.musique/2) == -1)quitter(SDL_MIXER);
        if(Mix_Volume(1, jeu_parametres.effets) == -1)quitter(SDL_MIXER);
        if(Mix_Volume(2, jeu_parametres.effets) == -1)quitter(SDL_MIXER);
        if(Mix_Volume(3, jeu_parametres.effets) == -1)quitter(SDL_MIXER);
        if(Mix_Volume(4, jeu_parametres.effets) == -1)quitter(SDL_MIXER);
        if(Mix_Volume(5, jeu_parametres.dialogues) == -1)quitter(SDL_MIXER);
        if(Mix_Volume(6, jeu_parametres.musique/2) == -1)quitter(SDL_MIXER);
    }
}

/**
 * \fn void detruire_musique(int extra)
 * \brief Cette fonction permet de libérer la musique stocker dans le tableau jeu_parametres.musiques[]
 */
void detruire_musique(int extra)
{
    Mix_FreeChunk(jeu_parametres.musiques[extra]);
}
