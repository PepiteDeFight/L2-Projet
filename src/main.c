/**
 * @file        main.c
 * @brief       Contient l'implémentation de la fonction int main() ainsi que tous les appels de librairies dynamiques pour sdl
 * @author      Meunier Rodrigue Nicolas Lemoult Mathis Morisseau
 * @version     1.0
 * @date        2021
 * @copyright   Le Mans Université
 */

#include "../lib/struct.h"

/**
 * \fn int main(int argc, char* argv[])
 * \brief La fonction main ne sert qu'a appelé la fonction accueil et démarage et surtout à appeler les libraires dynamiques SDL
 *
 * \param argc Nombre d'arguments
 * \param argv Contient les arguments
 * \return 0 si aucune erreur
 */
int main(int argc, char* argv[])
{
    /*      INITIALISATION DES LIBRAIRIES DYNAMQIUES        */
    errno=0;
    if(SDL_Init(SDL_INIT_EVERYTHING) !=0)quitter(SDL_BASE);
    if( !(IMG_Init(IMG_INIT_PNG)) )quitter(SDL_IMAGE);
    if(TTF_Init() != 0)quitter(SDL_TTF);
    if(!Mix_Init(MIX_INIT_MP3))quitter(SDL_MIXER);
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)quitter(SDL_MIXER); //Initialisation de l'API Mixer

    /*------------------------------------------------------*/
    initialisation_parametres();
    //menu_parametre();
    accueil();
    //SDL_Delay(5000);
    quitter(QUITTER);
    return 0;
}
