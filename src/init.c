/**
 * @file        init.c
 * @brief       Contient l'implémentation des fonctions d'initialisation, comme la police, les variables, les structures . . .
 * @author      Meunier Rodrigue Nicolas Lemoult Mathis Morisseau
 * @version     1.0
 * @date        2021
 * @copyright   Le Mans Université
 */
#include "../include/init.h"

/**
 * \fn void initialisation_Textures()
 * \brief La plupart des textures sont rechargées si elles sont à NULL, Il faut donc les initialiser à NULL pour les charger au moins une fois. Cette fonction met les textures en questions à NULL
 */
void initialisation_Textures()
{
    struct_jeu.texture_accueil=NULL;
    struct_jeu.texture_multijoueur=NULL;
    struct_jeu.transition=NULL;
    struct_jeu.selection_personnages=NULL;
    struct_jeu.selecteur=NULL;
    struct_jeu.texture_fps=NULL;
    struct_jeu.vie_joueurs=NULL;
    struct_jeu.texture_rect_vie=NULL;
    for(int i=0; i<4; i++)
        for(int j=0; j<6; j++)
            for(int k=0; k<9; k++)
                struct_jeu.textures_personnages_joueurs[i][j][k]=NULL;
}
/**
 * \fn void initialisation_parametres()
 * \brief Cette fonction permet d'initialiser la plupart des structures et d'appeler les fonctions pour créer la fenetre, lancer l'écran de chargement et récupérer les parametres utilisateur comme les contrôles
 */
void initialisation_parametres()
{
    //R�cup�rations des parametres (controls,...)
    chargement_parametres();
    initialisation_fps();
    initialisation_Textures();
    struct_jeu.ticks_depart=SDL_GetTicks();
    struct_jeu.ticks_evo=struct_jeu.ticks_depart;
    struct_jeu.ticks_actions=struct_jeu.ticks_depart;
    struct_jeu.debug=fopen(SRC_FICHIER_DEBUG,"w");
    //D�marrage des fonctions n�c�ssaires � l'affichage
    definir_resolutions();
    creation_fenetre();
    modifier_window();

    //chargement des textures
    chargerTextures();
    struct_jeu.frequence_video=0;//on initialise la variable qui g�re les textures de fond de vid�o d'accueil
    struct_jeu.texture_plateau_jeu_selectione=0;

    //Chargement de la police
    chargement_police(TAILLE_POLICE_T1);

    //Chargement de la musique d'intro

    creation_canaux_musique();
    chargement_musique(6,MUSIQUE_INTRO,0);
    changement_volumes_musiques();

    //affichage de l'�cran de chargement (d�marrage)
    chargement_demarrage();
    detruire_musique(MUSIQUE_INTRO);

}

/**
 * \fn void chargement_police(int taille)
 * \brief Cette fonction permet de chnager la taille de la police (cf defs.h -> différentes tailles de police)
 * \param taille Correspond à la taille choisie
 */
void chargement_police(int taille)
{
    TTF_CloseFont(struct_jeu.police);
    struct_jeu.police=NULL;
    struct_jeu.police=TTF_OpenFont(POLICE,taille);
    if(struct_jeu.police==NULL)quitter(SDL_TTF);
}


/**
 * \fn void chargement_parametres()
 * \brief Cette fonction permet de sois crééer le fichier de sauvegarde des parametres sois de récupérer les parametres sauvegardés
 */
void chargement_parametres() //Cette fonction � pour but de r�cup�rer les contr�les sauvegard�s; Si jamais des contr�les sont perdu ou in�xistants, la fonction remet/met par d�fault des contr�les
{
    FILE *f_parametres=NULL;
    f_parametres=fopen(SRC_FICHIER_PARA,"r");
    if(errno==2) //si fichier introuvable alors cr�ation du fichier
    {
        fclose(f_parametres);
        f_parametres=fopen(SRC_FICHIER_PARA,"w");
        fprintf(f_parametres,"-GRAPHISMES-\nMode : %d\nResolution : %d\nFps : %d\nAfficherFps : %d\n-INTERFACE-\nEchelle : %d\n-AUDIO-\nMusique : %d\nEffets : %d\nDialogues : %d\nArrierePlan : %d\n-C-O-N-T-R-O-L-E-S-\n_JOUEUR1_\nAvancer : %d\nReculer : %d\nSauter : : %d\nAttaquer : %d\n_JOUEUR2_\nAvancer : %d\nReculer : %d\nSauter : %d\nAttaquer : %d\n_JOUEUR3_\nAvancer : %d\nReculer : %d\nSauter : %d\nAttaquer : %d\n_JOUEUR4_\nAvancer : %d\nReculer : %d\nSauter : %d\nAttaquer : %d\n", DEF_MODE, DEF_RESO, DEF_FPS, DEF_AFFPS, DEF_ECHELLE, DEF_SOUND,DEF_SOUND, DEF_SOUND, 1, DEF_AVANCER1, DEF_RECULER1, DEF_SAUTER1, DEF_ATTAQUE1, DEF_AVANCER2, DEF_RECULER2, DEF_SAUTER2, DEF_ATTAQUE2, DEF_AVANCER3, DEF_RECULER3, DEF_SAUTER3, DEF_ATTAQUE3, DEF_ATTAQUE4, DEF_RECULER4, DEF_SAUTER4, DEF_ATTAQUE4);
        fclose(f_parametres);
        f_parametres=fopen(SRC_FICHIER_PARA,"r");
    }
    fscanf(f_parametres,"-GRAPHISMES-\nMode : %d\nResolution : %d\nFps : %d\nAfficherFps : %d\n-INTERFACE-\nEchelle : %d\n-AUDIO-\nMusique : %d\nEffets : %d\nDialogues : %d\nArrierePlan : %d\n-C-O-N-T-R-O-L-E-S-\n_JOUEUR1_\nAvancer : %d\nReculer : %d\nSauter : : %d\nAttaquer : %d\n_JOUEUR2_\nAvancer : %d\nReculer : %d\nSauter : : %d\nAttaquer : %d\n_JOUEUR3_\nAvancer : %d\nReculer : %d\nSauter : %d\nAttaquer : %d\n_JOUEUR4_\nAvancer : %d\nReculer : %d\nSauter : %d\nAttaquer : %d\n", &jeu_parametres.mode, &jeu_parametres.resolution, &jeu_parametres.fps, &jeu_parametres.affichFPS, &jeu_parametres.echelle, &jeu_parametres.musique, &jeu_parametres.effets, &jeu_parametres.dialogues, &jeu_parametres.arriere_plan, &jeu_parametres.avancer1, &jeu_parametres.reculer1, &jeu_parametres.sauter1, &jeu_parametres.attaquer1, &jeu_parametres.avancer2, &jeu_parametres.reculer2, &jeu_parametres.sauter2, &jeu_parametres.attaquer2, &jeu_parametres.avancer3, &jeu_parametres.reculer3, &jeu_parametres.sauter3, &jeu_parametres.attaquer3, &jeu_parametres.avancer4, &jeu_parametres.reculer4, &jeu_parametres.sauter4, &jeu_parametres.attaquer4);
    fclose(f_parametres);
}

/**
* \fn void sauvegarde_parametres()
* \brief Cette fonction permet de sauvegarder les parametres utilisateur dans le fichier de sauvegarde
*/
void sauvegarde_parametres()
{
    FILE *f_parametres=NULL;
    f_parametres=fopen(SRC_FICHIER_PARA,"w");
    fprintf(f_parametres,"-GRAPHISMES-\nMode : %d\nResolution : %d\nFps : %d\nAfficherFps : %d\n-INTERFACE-\nEchelle : %d\n-AUDIO-\nMusique : %d\nEffets : %d\nDialogues : %d\nArrierePlan : %d\n-C-O-N-T-R-O-L-E-S-\n_JOUEUR1_\nAvancer : %d\nReculer : %d\nSauter : : %d\nAttaquer : %d\n_JOUEUR2_\nAvancer : %d\nReculer : %d\nSauter : : %d\nAttaquer : %d\n_JOUEUR3_\nAvancer : %d\nReculer : %d\nSauter : : %d\nAttaquer : %d\n_JOUEUR4_\nAvancer : %d\nReculer : %d\nSauter : : %d\nAttaquer : %d\n", jeu_parametres.mode, jeu_parametres.resolution, jeu_parametres.fps, jeu_parametres.affichFPS, jeu_parametres.echelle, jeu_parametres.musique, jeu_parametres.effets, jeu_parametres.dialogues, jeu_parametres.arriere_plan, jeu_parametres.avancer1, jeu_parametres.reculer1, jeu_parametres.sauter1, jeu_parametres.attaquer1, jeu_parametres.avancer2, jeu_parametres.reculer2, jeu_parametres.sauter2, jeu_parametres.attaquer2, jeu_parametres.avancer3, jeu_parametres.reculer3, jeu_parametres.sauter3, jeu_parametres.attaquer3, jeu_parametres.avancer4, jeu_parametres.reculer4, jeu_parametres.sauter4, jeu_parametres.attaquer4);
    fclose(f_parametres);
}

/**
 * \fn void quitter(int code)
 * \brief Cette fonction permet de terminer le programme en faisant apparaitre une popup permettant à l'utilisateur de sois mettre fin au programme sois poursuivre malgré l'erreur
 * \param code Corrrespond au code d'erreur d'appel de la fonction (cf defs.h -> code d'erreurs)
 */
void quitter(int code)
{
    char erreur[30];
    switch(code)
    {
    case QUITTER    :
        strcpy(erreur,"NULL");
        break;
    case FOPEN_ERR  :
        strcpy(erreur,strerror(errno));
        break;
    case SDL_IMAGE  :
        strcpy(erreur,IMG_GetError());
        break;
    case SDL_BASE   :
        strcpy(erreur,SDL_GetError());
        break;
    case SDL_TTF    :
        strcpy(erreur,TTF_GetError());
        break;
    case SDL_MIXER  :
        strcpy(erreur,Mix_GetError());
        break;
    case RESEAU     :
        strcpy(erreur,"Réseau/socket");
        break;
    default         :
        strcpy(erreur,"default code NULL");
        break;
    }
    fprintf ( stdout,"\nErreur : %s \n", erreur); //on �crit l'erreur dans le terminal
    if(code == QUITTER || !creation_popup_erreur(erreur)) //si la fonction creation_popup renvoie 0 alors l'utilisateur � d�cid� de mettre fin au programme le code QUITTER permet de mettre d�f�nitivement fin au programme sans demand� � l'utilisateur (exemple : bouton quitter dans l'accueil)
    {
        // PENSER A AJOUTER TOUS LES FREE DES STRUCTURES
        Mix_CloseAudio();
        TTF_CloseFont(struct_jeu.police);
        SDL_Quit();
        IMG_Quit();
        TTF_Quit();
        fclose(struct_jeu.debug);
        abort();
    }
}

void write_all_varia()
{
    for(int i = 0; i < 4; i++)
    {
        fprintf(struct_jeu.debug, "Joueur %d : Vie : %d, Type de Personnage : %d, Evolution : %d, Direction : %d, Position X : %f, Position Y : %f, Modification : %d, Jump : %d\n\n",
                struct_jeu.joueurs[i].vie, struct_jeu.joueurs[i].etat, struct_jeu.joueurs[i].evolution, struct_jeu.joueurs[i].direction, struct_jeu.joueurs[i].positionX, struct_jeu.joueurs[i].positionY, struct_jeu.joueurs[i].modification, struct_jeu.joueurs[i].jump);
    }
    fprintf(struct_jeu.debug, "Paramètre : Mode : %d, Resolution : %d, Fps : %d, AfficheFPS : %d\nPlageFPS[0] : %d, PlageFPS[1] : %d, PlageFPS[2] : %d, PlageFPS[3] : %d,  PlageFPS[4] : %d, PlageFPS[5] : %d\n",
            jeu_parametres.mode, jeu_parametres.resolution, jeu_parametres.fps, jeu_parametres.affichFPS, jeu_parametres.plageFPS[0], jeu_parametres.plageFPS[1], jeu_parametres.plageFPS[2], jeu_parametres.plageFPS[3], jeu_parametres.plageFPS[4], jeu_parametres.plageFPS[5]);
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<10; j++)
        {
            fprintf(struct_jeu.debug, "Resolution[%d][%d] : %d. ", i, j, jeu_parametres.reso[i][j]);
        }
    }
    fprintf(struct_jeu.debug, "\n\nEchelle : %d, Musique : %d, Effets : %d, Dialogues : %d, Arrière Plan : %d\nJoueur 1 : Avancer : %d, Reculer : %d, Sauter : %d, Attaquer : %d\nJoueur 2 : Avancer : %d, Reculer : %d, Sauter : %d, Attaquer : %d\nJoueur 3 : Avancer : %d, Reculer : %d, Sauter : %d, Attaquer : %d\nJoueur 4 : Avancer : %d, Reculer : %d, Sauter : %d, Attaquer : %d\nPage : %d\n\n",
            jeu_parametres.echelle, jeu_parametres.effets, jeu_parametres.dialogues, jeu_parametres.arriere_plan, jeu_parametres.avancer1, jeu_parametres.reculer1, jeu_parametres.sauter1, jeu_parametres.attaquer1, jeu_parametres.avancer2, jeu_parametres.reculer2, jeu_parametres.sauter2, jeu_parametres.attaquer2,jeu_parametres.avancer3, jeu_parametres.reculer3, jeu_parametres.sauter3, jeu_parametres.attaquer3,jeu_parametres.avancer4, jeu_parametres.reculer4, jeu_parametres.sauter4, jeu_parametres.attaquer4, jeu_parametres.page);

    fprintf(struct_jeu.debug, "Choix Résolution : %d, Fréquence Vidéo : %d, FPS Moyen : %d, FPS Maximum : %d, FPS Minimum : %d\n",
            struct_jeu.choix_resolution, struct_jeu.frequence_video, struct_jeu.fpsMoy, struct_jeu.fpsMax, struct_jeu.fpsMin);

    for(int i=0; i<20; i++)
    {
        fprintf(struct_jeu.debug, "Tableau FPS [%d] : %d. ", i, struct_jeu.tableau_fps[i]);
    }
    fprintf(struct_jeu.debug, "\nPerte De Focus : %d, Texture du Plateau Séléctionner : %d, Perte-Vie : %d\nFrame Evolution : %d, Nombre de Joueur : %d, En Résaux : %d\n",
            struct_jeu.focus_loose, struct_jeu.texture_plateau_jeu_selectione, struct_jeu.perte_vie, struct_jeu.frames_evolution, struct_jeu.nombre_joueurs, struct_jeu.reseauOn);

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            fprintf(struct_jeu.debug, "Tableau Evenement [%d][%d] : %d. ", i, j, struct_jeu.tableau_event[i][j]);
        }
    }
    fprintf(struct_jeu.debug, "\n\nTick de dépars : %d, Tick de Fin : %d, Tick d'évolution : %d, Tick D'action : %d\n\n",
            struct_jeu.ticks_depart, struct_jeu.ticks_fin, struct_jeu.ticks_evo, struct_jeu.ticks_actions);

    fprintf(struct_jeu.debug, "Socket Client : %d, Socket Serveur : %d, Longueur Mon Adresse : %d, Buffer : %s\n", sockets.socket_client, sockets.socket_serveur, sockets.mon_address_longueur, sockets.buffer);
}
