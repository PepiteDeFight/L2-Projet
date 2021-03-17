/**
 * @file        input.c
 * @brief       Contient l'implémentation des fonctions d'événements ainsi que de jeu
 * @author      Meunier Rodrigue Nicolas Lemoult Mathis Morisseau
 * @version     1.0
 * @date        2021
 * @copyright   Le Mans Université
 */
#include "../include/input.h"
/**
 * \fn int input_popup()
 * \brief Cette fonction gère l'entrée des événements de la popup d'erreur, dans le cas où une erreur survient (cf : quitter() -> init.c)
 *
 * \return RETOUR_QUITTER si l'utilisateur veut mettre fin au programme ou RETOUR_POURSUIVRE s'il souhaite poursuivre malgré l'erreur
 */
int input_popup()
{
    SDL_Event event;
    while(1)
    {
        while(SDL_PollEvent(&event))
            switch(event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.x>=XPOURSUIVRE_MIN && event.button.x<=XPOURSUIVRE_MAX && event.button.y>=YPOURSUIVRE_MIN && event.button.y<=YPOURSUIVRE_MAX)return RETOUR_POURSUIVRE;
                if(event.button.x>=XQUITTER_MIN && event.button.x<=XQUITTER_MAX && event.button.y>=YQUITTER_MIN && event.button.y<=YQUITTER_MAX)return RETOUR_QUITTER;
                break;
            case SDL_QUIT:
                return RETOUR_QUITTER;
            }
        delay();
    }
    return RETOUR_QUITTER;
}

/**
 * \fn void accueil()
 * \brief Cette fonction gère l'entrée des événements de l'accueil, c'est la fonction principale du programme, elle permet à l'utilisateur d'accéder au différents modes de jeu ainsi qu'aux paramètres et de quitter
 *
 */
void accueil()
{
    //on clear le visuel
    transition_visuelle();
    //on met la musique
    chargement_musique(0,MUSIQUE_ACCUEIL,INFINI);
    SDL_Event event;
    SDL_bool continuer=SDL_TRUE;
    SDL_bool partieOn=SDL_TRUE;
    while(continuer)
    {
        affichage_accueil();
        affichage_fps();
        rendre_affichage();
        while(SDL_PollEvent(&event))
            switch(event.type)
            {
            case SDL_QUIT:
                quitter(QUITTER);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_BOUTONS_ACCUEIL && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_BOUTONS_ACCUEIL) //si on se situe dans l'interval graphique des boutons
                {
                    if(event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_CAMPAGNE && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_CAMPAGNE) //Appuis du bouton Campagne par l'utilisateur
                    {
                        campagne();
                    }
                    if(event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_MULTIJOUEUR && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_MULTIJOUEUR) //Appuis du bouton Campagne par l'utilisateur
                    {
                        struct_jeu.nombre_joueurs=multijoueur();
                        if(struct_jeu.reseauOn)if(!choix_serveur())partieOn=SDL_FALSE;
                        if(struct_jeu.nombre_joueurs && partieOn)if(!choix_personnages())partieOn=SDL_FALSE;
                        if(struct_jeu.nombre_joueurs && partieOn)partie();
                        struct_jeu.nombre_joueurs=0;
                        struct_jeu.reseauOn=0;
                        partieOn=SDL_TRUE;
                    }
                    if(event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_PARAMETRES && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_PARAMETRES) //Appuis du bouton Campagne par l'utilisateur
                    {
                        menu_parametre();
                    }
                    if(event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_QUITTER && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_QUITTER) //Appuis du bouton Quitter par l'utilisateur
                    {
                        quitter(QUITTER);
                    }

                }
                break;
            case SDL_WINDOWEVENT:
                if(!jeu_parametres.arriere_plan)
                {
                    switch(event.window.event)
                    {
                    case SDL_WINDOWEVENT_MINIMIZED:
                        struct_jeu.focus_loose=1;
                        break;
                    case SDL_WINDOWEVENT_MAXIMIZED:
                        struct_jeu.focus_loose=0;
                        break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        struct_jeu.focus_loose=0;
                        break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        struct_jeu.focus_loose=1;
                        break;
                    }
                    changement_volumes_musiques();
                }
                break;
            }
        delay();
    }
}

/**
 * \fn void menu_parametre()
 * \brief Cette fonction gère l'entrée des événements du menu des parametre, cette fonction permet à l'utilisateur grâce à l'interface graphique de changer ses controles, ses fps etc...
 *
 */
void menu_parametre()
{
    decharger_Texture(&(struct_jeu.texture_accueil));
    int buffer;
    SDL_Event event;
    while(1)
    {
        afficher_details_parametres();
        affichage_fps();
        rendre_affichage();
        while(SDL_PollEvent(&event))
            switch(event.type)
            {
            case SDL_QUIT:
                sauvegarde_parametres();
                quitter(QUITTER);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]/RAPPORT_PARAMETRE_CHOIX) //Selection du menu en question (parametre / audio / . . .
                {
                    if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_AFFICHAGE && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_AFFICHAGE)
                        jeu_parametres.page=PAGE_GRAPHISMES;
                    if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_AUDIO && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_AUDIO)
                        jeu_parametres.page=PAGE_AUDIO;
                    if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_CONTROLES && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_CONTROLES)
                        jeu_parametres.page=PAGE_CONTROLES;
                }
                switch(jeu_parametres.page)
                {
                case PAGE_GRAPHISMES:
                    if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_BM_MA && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_BM_MA && event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_BM_MA && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_BM_MA)
                    {
                        jeu_parametres.mode=0;
                        modifier_window();
                    }//si on appuis sur le bouton (-) pour le mode d'affichage
                    if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_BP_MA && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_BP_MA && event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_BP_MA && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_BP_MA)
                    {
                        jeu_parametres.mode=1;
                        modifier_window();
                    }//si on appuis sur le bouton (+) pour le mode d'affichage

                    if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_BM_RE && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_BM_RE && event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_BM_RE && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_BM_RE && !jeu_parametres.mode)
                    {
                        if(jeu_parametres.resolution>0)
                        {
                            jeu_parametres.resolution--;
                            modifier_window();
                        }
                    }//si on appuis sur le bouton (-) pour la r�solution
                    if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.resolution]*XRAPPORT_BP_RE && event.button.x<=jeu_parametres.reso[0][jeu_parametres.resolution]*XMAXRAPPORT_BP_RE && event.button.y>=jeu_parametres.reso[1][jeu_parametres.resolution]*YRAPPORT_BP_RE && event.button.y<=jeu_parametres.reso[1][jeu_parametres.resolution]*YMAXRAPPORT_BP_RE && !jeu_parametres.mode)
                    {
                        if(jeu_parametres.resolution<8)
                        {
                            jeu_parametres.resolution++;
                            modifier_window();
                        }
                    }//si on appuis sur le bouton (+) pour la r�solution
                    if(jeu_parametres.mode)
                    {
                        if(event.button.x>=jeu_parametres.reso[0][9]*XRAPPORT_BM_MA && event.button.x<=jeu_parametres.reso[0][9]*XMAXRAPPORT_BM_MA && event.button.y>=jeu_parametres.reso[1][9]*YRAPPORT_BM_MA && event.button.y<=jeu_parametres.reso[1][9]*YMAXRAPPORT_BM_MA)
                        {
                            if(jeu_parametres.mode>0)
                            {
                                jeu_parametres.mode--;
                                modifier_window();
                            }
                        }//si on appuis sur le bouton (-) pour le mode d'affichage et qu'on est en mode plein �cran
                    }
                    if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_BM_FPS && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_BM_FPS && event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_BM_FPS && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_BM_FPS)
                    {
                        if(jeu_parametres.fps>0)
                        {
                            jeu_parametres.fps--;
                            modifier_window();
                        }

                    }//si on appuis sur le bouton (-) pour les FPS
                    if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_BP_FPS && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_BP_FPS && event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_BP_FPS && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_BP_FPS)
                    {
                        if(jeu_parametres.fps<5)
                        {
                            jeu_parametres.fps++;
                            modifier_window();
                        }

                    }//si on appuis sur le bouton (+) pour les FPS;
                    if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_BOUTON_AFPS && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_BOUTON_AFPS && event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_BOUTON_AFPS && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_BOUTON_AFPS)
                    {
                        if(jeu_parametres.affichFPS)jeu_parametres.affichFPS=0;
                        else jeu_parametres.affichFPS=1;

                    }//si on appuis sur le bouton pour afficher les FPS;

                    break;
                case PAGE_AUDIO:
                    if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_CUR_MUS && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_CUR_MUS && event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_CUR_MUS && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_CUR_MUS)
                    {
                        while(event.type != SDL_MOUSEBUTTONUP)
                        {
                            SDL_PollEvent(&event);
                            buffer=100*((int)(event.button.x-XRAPPORT_CUR_MUS*jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]))/((int)((XMAXRAPPORT_CUR_MUS-XRAPPORT_CUR_MUS)*jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]));
                            if(buffer <=100 && buffer >=0)jeu_parametres.musique=buffer;
                            afficher_details_parametres();
                            affichage_fps();
                            rendre_affichage();
                        }
                    }//si on appuis sur le curseur de la musique

                    if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_CUR_EFS && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_CUR_EFS && event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_CUR_EFS && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_CUR_EFS)
                    {

                        while(event.type != SDL_MOUSEBUTTONUP)
                        {
                            SDL_PollEvent(&event);
                            buffer=100*((int)(event.button.x-XRAPPORT_CUR_EFS*jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]))/((int)((XMAXRAPPORT_CUR_EFS-XRAPPORT_CUR_EFS)*jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]));
                            if(buffer <=100 && buffer >=0)jeu_parametres.effets=buffer;
                            afficher_details_parametres();
                            affichage_fps();
                            rendre_affichage();
                        }

                    }//si on appuis sur le curseur des effets sonores
                    if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_CUR_DIA && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_CUR_DIA && event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_CUR_DIA && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_CUR_DIA)
                    {
                        while(event.type != SDL_MOUSEBUTTONUP)
                        {
                            SDL_PollEvent(&event);
                            buffer=100*((int)(event.button.x-XRAPPORT_CUR_DIA*jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]))/((int)((XMAXRAPPORT_CUR_DIA-XRAPPORT_CUR_DIA)*jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]));
                            if(buffer <=100 && buffer >=0)jeu_parametres.dialogues=buffer;
                            afficher_details_parametres();
                            affichage_fps();
                            rendre_affichage();
                        }
                    }//si on appuis sur le curseur des effets sonores
                    if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_BOUTON_SAP && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_BOUTON_SAP && event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_BOUTON_SAP && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_BOUTON_SAP && jeu_parametres.dialogues<100)
                    {
                        if(jeu_parametres.arriere_plan)jeu_parametres.arriere_plan=0;
                        else jeu_parametres.arriere_plan=1;
                    }//si on appuis sur le bouton pour activer les sons en arri�re plan
                    changement_volumes_musiques();


                    break;
                case PAGE_CONTROLES:
                    break;


                }
                if(event.button.y>=YRAPPORT_BOUTON_VALID*jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution] && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_BOUTON_VALID)
                {
                    if(event.button.x>=XRAPPORT_BOUTON_RESET*jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution] && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_BOUTON_RESET)
                    {
                        remove(SRC_FICHIER_PARA);
                        chargement_parametres();
                        modifier_window();
                        changement_volumes_musiques();
                    }
                    if(event.button.x>=XRAPPORT_BOUTON_BACK*jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution] && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_BOUTON_BACK)
                    {
                        changement_volumes_musiques();
                        sauvegarde_parametres();
                        return;
                    }
                }//boutons de validation appuis � la souris

                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                case SDLK_r:
                    remove(SRC_FICHIER_PARA);
                    chargement_parametres();
                    changement_volumes_musiques();
                    sauvegarde_parametres();
                    break;
                case SDLK_ESCAPE:
                    changement_volumes_musiques();
                    sauvegarde_parametres();
                    return;

                }
                break;
            case SDL_WINDOWEVENT:
                if(!jeu_parametres.arriere_plan)
                {
                    switch(event.window.event)
                    {
                    case SDL_WINDOWEVENT_MINIMIZED:
                        struct_jeu.focus_loose=1;
                        break;
                    case SDL_WINDOWEVENT_MAXIMIZED:
                        struct_jeu.focus_loose=0;
                        break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        struct_jeu.focus_loose=0;
                        break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        struct_jeu.focus_loose=1;
                        break;
                    }
                    changement_volumes_musiques();
                }
                break;
            }
        delay();
    }
}

/**
 * \fn void campagne()
 * \brief Cette fonction gère les événements du menu campagne pour une éventuelle partie en solo
 *
 */
void campagne()
{

}
/**
 * \fn int multijoueur()
 * \brief Contrairement à campagne la fonction multijoueur permet de récupérer la façon dont une partie va se déroulé, elle permet également de savoir si une partie va se dérouler en réseau ou non
 *
 * \return nombre_joueurs (2/4) ou 0 si abandon
 */
int multijoueur()
{
    transition_visuelle();
    decharger_Texture(&(struct_jeu.texture_accueil));
    afficher_ecran_multijoueur();
    rendre_affichage();
    SDL_Event event;
    while(1)
    {
        while(SDL_PollEvent(&event))
            switch(event.type)
            {
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    return 0;
            case SDL_QUIT:
                quitter(QUITTER);
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_BOUTON_2JL && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_BOUTON_2JL && event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_BOUTON_2JL && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_BOUTON_2JL)
                {
                    struct_jeu.reseauOn=0;
                    return 2;
                }//si on appuis sur le bouton 2 J local
                if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_BOUTON_4JL && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_BOUTON_4JL && event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_BOUTON_4JL && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_BOUTON_4JL)
                {
                    struct_jeu.reseauOn=0;
                    return 4;
                }//si on appuis sur le bouton 4 J local
                if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_BOUTON_2JR && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_BOUTON_2JR && event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_BOUTON_2JR && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_BOUTON_2JR)
                {
                    struct_jeu.reseauOn=1;
                    return 2;
                }//si on appuis sur le bouton 2 J reseau
                if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_BOUTON_4JR && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_BOUTON_4JR && event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_BOUTON_4JR && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_BOUTON_4JR)
                {
                    struct_jeu.reseauOn=1;
                    return 4;
                }//si on appuis sur le bouton 4 J reseau
                break;




            }
    }
    return 0;

}

/**
 * \fn void partie()
 * \brief La fonction coeur du jeu, elle permet de faire une partie du jeu en multijoueur, cette fonction récupère les actions/events des joueurs et appelle les fonctions d'actions.c pour mouvoir, faire attacker les joueurs
 *
 *
 */
void partie()
{
    transition_visuelle();
    SDL_Event event;
    struct_jeu.joueurs[0].positionX=410;//JOUEUR 1
    struct_jeu.joueurs[1].positionX=1560;//JOUEUR 2
    struct_jeu.joueurs[2].positionX=530;//JOUEUR 3
    struct_jeu.joueurs[3].positionX=1440;//JOUEUR 4
    for(;;)
    {
        //printf("Boucle %d avec %d\n", a++, SDL_GetTicks());
        afficher_partie();
        afficher_joueurs();
        afficher_vie_joueurs();
        affichage_fps();
        rendre_affichage();
        while(SDL_PollEvent(&event))
            switch(event.type)
            {
            case SDL_QUIT:
                quitter(QUITTER);
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == jeu_parametres.avancer1)struct_jeu.tableau_event[J1][0]=SDL_TRUE;
                if(event.key.keysym.sym == jeu_parametres.avancer2)struct_jeu.tableau_event[J2][0]=SDL_TRUE;
                if(event.key.keysym.sym == jeu_parametres.avancer3)struct_jeu.tableau_event[J3][0]=SDL_TRUE;
                if(event.key.keysym.sym == jeu_parametres.avancer4)struct_jeu.tableau_event[J4][0]=SDL_TRUE;

                if(event.key.keysym.sym == jeu_parametres.reculer1)struct_jeu.tableau_event[J1][1]=SDL_TRUE;
                if(event.key.keysym.sym == jeu_parametres.reculer2)struct_jeu.tableau_event[J2][1]=SDL_TRUE;
                if(event.key.keysym.sym == jeu_parametres.reculer3)struct_jeu.tableau_event[J3][1]=SDL_TRUE;
                if(event.key.keysym.sym == jeu_parametres.reculer4)struct_jeu.tableau_event[J4][1]=SDL_TRUE;

                if(event.key.keysym.sym == jeu_parametres.sauter1)struct_jeu.tableau_event[J1][2]=SDL_TRUE;
                if(event.key.keysym.sym == jeu_parametres.sauter2)struct_jeu.tableau_event[J2][2]=SDL_TRUE;
                if(event.key.keysym.sym == jeu_parametres.sauter3)struct_jeu.tableau_event[J3][2]=SDL_TRUE;
                if(event.key.keysym.sym == jeu_parametres.sauter4)struct_jeu.tableau_event[J4][2]=SDL_TRUE;

                if(event.key.keysym.sym == jeu_parametres.attaquer1)struct_jeu.tableau_event[J1][3]=SDL_TRUE;
                if(event.key.keysym.sym == jeu_parametres.attaquer2)struct_jeu.tableau_event[J2][3]=SDL_TRUE;
                if(event.key.keysym.sym == jeu_parametres.attaquer3)struct_jeu.tableau_event[J3][3]=SDL_TRUE;
                if(event.key.keysym.sym == jeu_parametres.attaquer4)struct_jeu.tableau_event[J4][3]=SDL_TRUE;


                if(event.key.keysym.sym == SDLK_ESCAPE)jeu_pause();
                break;
            case SDL_KEYUP:
                if(event.key.keysym.sym == jeu_parametres.avancer1)
                {
                    struct_jeu.joueurs[J1].modification=0;
                    struct_jeu.tableau_event[J1][0]=SDL_FALSE;
                }
                if(event.key.keysym.sym == jeu_parametres.avancer2)
                {
                    struct_jeu.joueurs[J2].modification=0;
                    struct_jeu.tableau_event[J2][0]=SDL_FALSE;
                }
                if(event.key.keysym.sym == jeu_parametres.avancer3)
                {
                    struct_jeu.joueurs[J3].modification=0;
                    struct_jeu.tableau_event[J3][0]=SDL_FALSE;
                }
                if(event.key.keysym.sym == jeu_parametres.avancer4)
                {
                    struct_jeu.joueurs[J4].modification=0;
                    struct_jeu.tableau_event[J4][0]=SDL_FALSE;
                }

                if(event.key.keysym.sym == jeu_parametres.reculer1)
                {
                    struct_jeu.joueurs[J1].modification=0;
                    struct_jeu.tableau_event[J1][1]=SDL_FALSE;
                }
                if(event.key.keysym.sym == jeu_parametres.reculer2)
                {
                    struct_jeu.joueurs[J2].modification=0;
                    struct_jeu.tableau_event[J2][1]=SDL_FALSE;
                }
                if(event.key.keysym.sym == jeu_parametres.reculer3)
                {
                    struct_jeu.joueurs[J3].modification=0;
                    struct_jeu.tableau_event[J3][1]=SDL_FALSE;
                }
                if(event.key.keysym.sym == jeu_parametres.reculer4)
                {
                    struct_jeu.joueurs[J4].modification=0;
                    struct_jeu.tableau_event[J4][1]=SDL_FALSE;
                }

                if(event.key.keysym.sym == jeu_parametres.sauter1)
                {
                    struct_jeu.joueurs[J1].modification=0;
                    struct_jeu.tableau_event[J1][2]=SDL_FALSE;
                }
                if(event.key.keysym.sym == jeu_parametres.sauter2)
                {
                    struct_jeu.joueurs[J2].modification=0;
                    struct_jeu.tableau_event[J2][2]=SDL_FALSE;
                }
                if(event.key.keysym.sym == jeu_parametres.sauter3)
                {
                    struct_jeu.joueurs[J3].modification=0;
                    struct_jeu.tableau_event[J3][2]=SDL_FALSE;
                }
                if(event.key.keysym.sym == jeu_parametres.sauter4)
                {
                    struct_jeu.joueurs[J4].modification=0;
                    struct_jeu.tableau_event[J4][2]=SDL_FALSE;
                }

                if(event.key.keysym.sym == jeu_parametres.attaquer1)
                {
                    struct_jeu.joueurs[J1].modification=0;
                    struct_jeu.tableau_event[J1][3]=SDL_FALSE;
                }
                if(event.key.keysym.sym == jeu_parametres.attaquer2)
                {
                    struct_jeu.joueurs[J2].modification=0;
                    struct_jeu.tableau_event[J2][3]=SDL_FALSE;
                }
                if(event.key.keysym.sym == jeu_parametres.attaquer3)
                {
                    struct_jeu.joueurs[J3].modification=0;
                    struct_jeu.tableau_event[J3][3]=SDL_FALSE;
                }
                if(event.key.keysym.sym == jeu_parametres.attaquer4)
                {
                    struct_jeu.joueurs[J4].modification=0;
                    struct_jeu.tableau_event[J4][3]=SDL_FALSE;
                }

                break;
            }
        action_timer();
        affichage_fps();
        delay();
    }
}
/**
 * \fn int choix_serveur()
 * \brief Cette fonction permet de récupèrer l'ip du serveur sur lequel une éventuelle partie en réseau se déroulerais
 * \return 0 si abandon ou 1 si succès
 *
 */
int choix_serveur()
{
    return 0;
}
/**
 * \fn int choix_personnages()
 * \brief Cette fonction permet de savoir quel personnage chaque joueur va jouer
 * \return 0 si abandon ou 1 si succès
 *
 */
int choix_personnages()
{
    transition_visuelle();
    decharger_Texture(&(struct_jeu.texture_multijoueur));
    SDL_Event event;
    SDL_bool continuer=SDL_TRUE;
    int *tab_coords_selecteur=calloc(struct_jeu.nombre_joueurs,sizeof(int));
    for(int i=0; i<struct_jeu.nombre_joueurs; i++)
    {
        struct_jeu.joueurs[i].type_personnage=1;
        struct_jeu.joueurs[i].direction=(i%2?GAUCHE:DROITE);//le(s) joueur(s) 1( et 3) est(sont) contre(s) le(s) joueur(s) 2(et 4)
        struct_jeu.joueurs[i].etat=IDLE;
    }

    if(struct_jeu.nombre_joueurs==J4)
    {
        struct_jeu.joueurs[J3].positionX=410;//JOUEUR 3
        struct_jeu.joueurs[J4].positionX=1560;//JOUEUR 4
        struct_jeu.joueurs[J2].positionY=256;
        struct_jeu.joueurs[J4].positionY=768;
        struct_jeu.joueurs[J1].positionY=256;
        struct_jeu.joueurs[J3].positionY=768;
    }
    else
    {
        struct_jeu.joueurs[J1].positionY=512;
        struct_jeu.joueurs[J2].positionY=512;
    }

    struct_jeu.joueurs[J1].positionX=410;//JOUEUR 1
    struct_jeu.joueurs[J2].positionX=1560;//JOUEUR 2

    creation_textures_personnage(0);
    while(continuer)
    {
        affiche_choix_personnages(tab_coords_selecteur);
        rendre_affichage();
        while(SDL_PollEvent(&event))
            switch(event.type)
            {
            case SDL_QUIT:
                quitter(QUITTER);
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == jeu_parametres.avancer1 )
                {
                    if(tab_coords_selecteur[J1] <11)tab_coords_selecteur[J1]++;
                }
                if(event.key.keysym.sym == jeu_parametres.avancer2)
                {
                    if(tab_coords_selecteur[J2] <11)tab_coords_selecteur[J2]++;
                }
                if(event.key.keysym.sym == jeu_parametres.avancer3 && struct_jeu.nombre_joueurs==4)
                {
                    if(tab_coords_selecteur[J3] <11)tab_coords_selecteur[J3]++;
                }
                if(event.key.keysym.sym == jeu_parametres.avancer4 && struct_jeu.nombre_joueurs==4)
                {
                    if(tab_coords_selecteur[J4] <11)tab_coords_selecteur[J4]++;
                }

                if(event.key.keysym.sym == jeu_parametres.reculer1)
                {
                    if(tab_coords_selecteur[J1] >0)tab_coords_selecteur[J1]--;
                }
                if(event.key.keysym.sym == jeu_parametres.reculer2)
                {
                    if(tab_coords_selecteur[J2] >0)tab_coords_selecteur[J2]--;
                }
                if(event.key.keysym.sym == jeu_parametres.reculer3 && struct_jeu.nombre_joueurs==4)
                {
                    if(tab_coords_selecteur[J3] >0)tab_coords_selecteur[J3]--;
                }
                if(event.key.keysym.sym == jeu_parametres.reculer4 && struct_jeu.nombre_joueurs==4)
                {
                    if(tab_coords_selecteur[J4] >0)tab_coords_selecteur[J4]--;
                }
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    free(tab_coords_selecteur);
                    return 0;
                }
                if(event.key.keysym.sym == SDLK_RETURN)
                {
                    continuer=0;
                }
            }
        delay();
    }

    for(int i=0; i<struct_jeu.nombre_joueurs; i++) //on remplit les structures des joueurs avec les valeurs ad�quats restantes
    {
        struct_jeu.joueurs[i].vie=INIT_VIE;
        struct_jeu.joueurs[i].evolution=0;
        struct_jeu.joueurs[i].positionY=1030;
        struct_jeu.joueurs[i].modification=0;
        struct_jeu.joueurs[i].jump=0;
        struct_jeu.joueurs[i].type_personnage=((tab_coords_selecteur[i]/3))*10+(tab_coords_selecteur[i]%3)+1;

    }
    transition_visuelle();
    creation_textures_personnage();
    free(tab_coords_selecteur);
    struct_jeu.perte_vie=0;
    return 1;
}

int choix_plateau()
{
    /*
    if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_BM_CHOIX_PLAT && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_BM_CHOIX_PLAT && event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_BM_CHOIX_PLAT && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_BM_CHOIX_PLAT)
    {
        struct_jeu.texture_plateau_jeu_selectione--;
        if(struct_jeu.texture_plateau_jeu_selectione < 0)struct_jeu.texture_plateau_jeu_selectione=2;
    }//bouton moins
    if(event.button.x>=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XRAPPORT_BP_CHOIX_PLAT && event.button.x<=jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*XMAXRAPPORT_BP_CHOIX_PLAT && event.button.y>=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YRAPPORT_BP_CHOIX_PLAT && event.button.y<=jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*YMAXRAPPORT_BP_CHOIX_PLAT)
    {
        struct_jeu.texture_plateau_jeu_selectione++;
        if(struct_jeu.texture_plateau_jeu_selectione > 2)struct_jeu.texture_plateau_jeu_selectione=0;
    }//bouton plus
    break;
    */
    return 1;
}
/**
 * \fn void jeu_pause()
 * \brief Cette fonction permet de faire une pause tant que l'utilisateur n'a pas appuyer sur echape, elle n'est pas dans timer.c car elle n'agit pas directement sur le temps, elle fait une sorte de boucle sans changer l'affichage. Ps: disponible uniquement en local
 */
void jeu_pause()
{
    if(!struct_jeu.reseauOn)
    {
        afficher_pause();
        SDL_Event event;
        while(1)
        {
            while(SDL_PollEvent(&event))
                switch(event.type)
                {
                case SDL_QUIT:
                    quitter(QUITTER);
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE)return;
                }
            delay();
        }
    }
}
