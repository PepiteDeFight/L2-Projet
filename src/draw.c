/**
 * @file        draw.c
 * @brief       Contient toutes les fonctions en rapport avec l'affichage
 * @author      Meunier Rodrigue
 * @version     1.0
 * @date        2021
 * @copyright   Le Mans Université
 */

#include "include/draw.h"
SDL_Color couleurBlanc  =   {255,255,255,255};
SDL_Color couleurBleu   =   {0, 0, 255, 255};
SDL_Color couleurOrange =   {255, 140, 40, 255};
SDL_Color couleurVert   =   {0, 255, 0, 255};
SDL_Color couleurJaune  =   {255, 255, 0, 255};
SDL_Color couleurRose   =   {255, 110, 137, 255};
SDL_Color couleurRouge  =   {255, 0, 0, 255};
SDL_Color couleurNoir   =   {0, 0, 0, 255};
const int tab_rapport_X_vies[4]= {RAPPORT_X_J1_VIE,RAPPORT_X_J2_VIE,RAPPORT_X_J3_VIE,RAPPORT_X_J4_VIE};

/**
 * \fn void definir_resolutions()
 * \brief Cette fonction rempli le tableau de résolution
*/
void definir_resolutions()
{
    jeu_parametres.reso[0][0]=1280;
    jeu_parametres.reso[1][0]=800;
    jeu_parametres.reso[0][1]=1440;
    jeu_parametres.reso[1][1]=900;
    jeu_parametres.reso[0][2]=1680;
    jeu_parametres.reso[1][2]=1050;
    jeu_parametres.reso[0][3]=1920;
    jeu_parametres.reso[1][3]=1080;
    jeu_parametres.reso[0][4]=1920;
    jeu_parametres.reso[1][4]=1200;
    jeu_parametres.reso[0][5]=768;
    jeu_parametres.reso[1][5]=1024;
    jeu_parametres.reso[0][6]=1280;
    jeu_parametres.reso[1][6]=1024;
    jeu_parametres.reso[0][7]=320;
    jeu_parametres.reso[1][7]=480;
    jeu_parametres.reso[0][8]=1366;
    jeu_parametres.reso[1][8]=768;
}

/**
 * \fn void chargerTextures()
 * \brief Cette fonction charge en mémoire les textures globales comme celle de l'accueil ou encore celle des paramêtres
*/
void chargerTextures()
{
    // Cr�ation des textures pour les parametres
    SDL_Surface *surf;
    char *chaine=malloc(18*sizeof(char));
    strcpy(chaine,SRC_IMG_PARA);
    for(int i=0; i<9; i++)
    {
        surf=IMG_Load(chaine);
        if(surf == NULL)quitter(SDL_IMAGE);
        chaine[13]++;// cette ligne permet d'incr�menter le num�ro de l'image '1'.png
        jeu_parametres.tabMenu[i]=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
        SDL_FreeSurface(surf);
    }
    jeu_parametres.page=0;
    free(chaine);
    // Cr�ation de la texture de l'accueil
    surf=IMG_Load(SRC_IMG_ACCUEIL);
    if(surf==NULL)quitter(SDL_IMAGE);
    struct_jeu.texture_accueil=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
    if(struct_jeu.texture_accueil==NULL)quitter(SDL_BASE);
    SDL_FreeSurface(surf);

    //Cr�ation textures d'arri�re plan jeu
    chaine=malloc(26*sizeof(char));
    strcpy(chaine,SRC_IMG_JEU);
    for(int i=1; i<NB_IMG_FOND; i++)
    {
        surf=IMG_Load(chaine);
        if(surf == NULL)quitter(SDL_IMAGE);
        chaine[21]++;// cette ligne permet d'incr�menter le num�ro de l'image '1'.png
        struct_jeu.textures_fond_jeu[i-1]=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
        SDL_FreeSurface(surf);
    }
    free(chaine);
    //Cr�ation textures du plateau du jeu
    chaine=malloc(29*sizeof(char));
    strcpy(chaine,SRC_IMG_PLATEAU);
    for(int i=1; i<NB_IMG_PLATEAU+1; i++)
    {
        surf=IMG_Load(chaine);
        if(surf == NULL)quitter(SDL_IMAGE);
        chaine[24]++;// cette ligne permet d'incr�menter le num�ro de l'image '1'.png
        struct_jeu.textures_plateau_jeu[i-1]=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
        SDL_FreeSurface(surf);
    }
    free(chaine);
    // Cr�ation de la texture du menu multijoueur
    surf=IMG_Load(SRC_IMG_MULTI);
    if(surf==NULL)quitter(SDL_IMAGE);
    struct_jeu.texture_multijoueur=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
    if(struct_jeu.texture_multijoueur==NULL)quitter(SDL_BASE);
    SDL_FreeSurface(surf);
    //création des textures pour le menu choix personnage
    surf=IMG_Load(SRC_IMG_CHOIX_PERSONNAGE);
    if(surf==NULL)quitter(SDL_IMAGE);
    struct_jeu.selection_personnages=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
    if(struct_jeu.selection_personnages==NULL)quitter(SDL_BASE);
    SDL_FreeSurface(surf);

    surf=IMG_Load(SRC_IMG_PAD);
    if(surf==NULL)quitter(SDL_IMAGE);
    struct_jeu.pad=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
    if(struct_jeu.pad==NULL)quitter(SDL_BASE);
    SDL_FreeSurface(surf);


}
/**
 * \fn void creation_textures_personnage()
 * \brief Cette fonction créer les textures en fonction du choix du joueur sur son personnage
*/
void creation_textures_personnage()
{
    SDL_Surface *surf=NULL;
    char *chaine=NULL;
    for(int i=0; i<struct_jeu.nombre_joueurs; i++)
    {
        switch(struct_jeu.joueurs[i].type_personnage/10)
        {
        case 0:
            chaine=malloc(sizeof(char)*strlen(SRC_IMG_PERSONNAGE_CHEVALIER));
            strcpy(chaine,SRC_IMG_PERSONNAGE_CHEVALIER);
            chaine[30]='0'+((struct_jeu.joueurs[i].type_personnage)%10);
            for(int y=0; y<6; y++)
                for(int z=0; z<10; z++)
                {
                    chaine[32]='0'+y;
                    chaine[34]='0'+z;
                    surf=IMG_Load(chaine);
                    if(surf==NULL)quitter(SDL_IMAGE);
                    struct_jeu.textures_personnages_joueurs[i][y][z]=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
                    SDL_FreeSurface(surf);
                }
            break;
        case 1:
            chaine=malloc(sizeof(char)*strlen(SRC_IMG_PERSONNAGE_ELFE));
            strcpy(chaine,SRC_IMG_PERSONNAGE_ELFE);
            chaine[25]='0'+(struct_jeu.joueurs[i].type_personnage)%10;
            for(int y=0; y<6; y++)
                for(int z=0; z<10; z++)
                {
                    chaine[27]='0'+y;
                    chaine[29]='0'+z;
                    surf=IMG_Load(chaine);
                    if(surf==NULL)quitter(SDL_IMAGE);
                    struct_jeu.textures_personnages_joueurs[i][y][z]=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
                    SDL_FreeSurface(surf);
                }
            break;
        case 2:
            chaine=malloc(sizeof(char)*strlen(SRC_IMG_PERSONNAGE_FEE));
            strcpy(chaine,SRC_IMG_PERSONNAGE_FEE);
            chaine[24]='0'+(struct_jeu.joueurs[i].type_personnage)%10;
            for(int y=0; y<6; y++)
                for(int z=0; z<10; z++)
                {
                    chaine[26]='0'+y;
                    chaine[28]='0'+z;
                    surf=IMG_Load(chaine);
                    if(surf==NULL)quitter(SDL_IMAGE);
                    struct_jeu.textures_personnages_joueurs[i][y][z]=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
                    SDL_FreeSurface(surf);
                }
            break;
        case 3:
            chaine=malloc(sizeof(char)*strlen(SRC_IMG_PERSONNAGE_WARRIOR));
            strcpy(chaine,SRC_IMG_PERSONNAGE_WARRIOR);
            chaine[28]='0'+(struct_jeu.joueurs[i].type_personnage)%10;
            for(int y=0; y<6; y++)
                for(int z=0; z<10; z++)
                {
                    chaine[30]='0'+y;
                    chaine[32]='0'+z;
                    surf=IMG_Load(chaine);
                    if(surf==NULL)quitter(SDL_IMAGE);
                    struct_jeu.textures_personnages_joueurs[i][y][z]=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
                    SDL_FreeSurface(surf);
                }
            break;
        }
        free(chaine);

    }
    if(struct_jeu.nombre_joueurs)
    {
        if(struct_jeu.nombre_joueurs==2)
        {
            surf=IMG_Load(SRC_IMG_VIE2J);

        }
        else if(struct_jeu.nombre_joueurs==4)
        {
            surf=IMG_Load(SRC_IMG_VIE4J);
        }
        if(surf==NULL)quitter(SDL_IMAGE);
        struct_jeu.vie_joueurs=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
        if(struct_jeu.vie_joueurs==NULL)quitter(SDL_BASE);
        SDL_FreeSurface(surf);
    }

}
/**
 * \fn void destruction_textures_personnage()
 * \brief Comme nous pouvons pas nous pemettre de stocker des Go de texture il faut libérer les textures, cette fonction s'en charge
*/
void destruction_textures_personnage()
{
    for(int i=0; i<4; i++)
        for(int j=0; j<6; j++)
            for(int k=0; k<9; k++)
                SDL_DestroyTexture(struct_jeu.textures_personnages_joueurs[i][j][k]);
}

/**
 * \fn void creation_fenetre()
 * \brief Cette fonction, appellée avant le chargement, créer la fenêtre qui accueillera les textures du jeu
*/
void creation_fenetre()
{
    SDL_Surface *icon=IMG_Load(SRC_IMG_ICON);
    struct_jeu.fenetre_jeu=NULL;
    struct_jeu.rendu_fenetre=NULL;
    struct_jeu.fenetre_jeu=SDL_CreateWindow("Pepite De Fight",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, jeu_parametres.reso[0][jeu_parametres.resolution], jeu_parametres.reso[1][jeu_parametres.resolution], 0);
    struct_jeu.rendu_fenetre=SDL_CreateRenderer(struct_jeu.fenetre_jeu,-1,SDL_RENDERER_ACCELERATED);
    if(struct_jeu.fenetre_jeu==NULL)quitter(SDL_BASE);
    if(struct_jeu.rendu_fenetre==NULL)quitter(SDL_BASE);
    SDL_SetWindowIcon(struct_jeu.fenetre_jeu,icon);
    SDL_FreeSurface(icon);
    SDL_SetWindowFullscreen(struct_jeu.fenetre_jeu,SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_GetWindowSize(struct_jeu.fenetre_jeu,&jeu_parametres.reso[0][9],&jeu_parametres.reso[1][9]);//r�cup�ration des dims max de la fen�tre
    SDL_SetWindowFullscreen(struct_jeu.fenetre_jeu,SDL_WINDOW_SHOWN);
    struct_jeu.focus_loose=0;
}
/**
 * \fn int creation_popup_erreur(char texte[30])
 * \brief Cette fonction affiche une popup en cas d'erreur avec écrit le code d'erreur en question
 * \param texte[30] Code d'erreur
 * \return 1 si l'utilisateur souhaite poursuivre malgré l'erreur ou 0 si arret
*/
int creation_popup_erreur(char texte[30])
{
    SDL_Window *popup=SDL_CreateWindow("Erreur detectee !",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,400,100,SDL_WINDOW_SHOWN);
    SDL_Renderer *rendu=SDL_CreateRenderer(popup,-1,SDL_RENDERER_SOFTWARE);
    chargement_police(TAILLE_POLICE_T7);
    SDL_Surface *text=TTF_RenderText_Solid(struct_jeu.police,texte,couleurJaune);
    SDL_Surface *surface=SDL_LoadBMP(SRC_IMG_POPUP);
    SDL_BlitSurface(text,NULL,surface,NULL);
    SDL_Texture *texture=SDL_CreateTextureFromSurface(rendu,surface);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(text);
    SDL_RenderCopy(rendu,texture,NULL,NULL);
    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(texture);
    if(input_popup())
    {
        SDL_DestroyWindow(popup);
        SDL_DestroyRenderer(rendu);
        return 1;
    }
    SDL_DestroyWindow(popup);
    SDL_DestroyRenderer(rendu);
    return 0;
}

/**
 * \fn void chargement_demarrage()
 * \brief Cette fonction réalise l'affichage de l'écran de démarrage du jeu, en affichant le logo
*/
void chargement_demarrage()
{
    SDL_Texture *texture_fond;
    SDL_Surface *surface=SDL_CreateRGBSurface(0, 1920, 1080, 32, 0,0,0,0);//Cr�ation d'une surface noir permettant de contenir le texte de d�marage du jeu
    int w=1920,h=1080;
    if(surface==NULL)quitter(SDL_BASE);
    texture_fond=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surface);
    if(texture_fond==NULL)quitter(SDL_BASE);
    if(SDL_RenderCopy(struct_jeu.rendu_fenetre, texture_fond, NULL, NULL))quitter(SDL_BASE);
    SDL_RenderPresent(struct_jeu.rendu_fenetre);
    //changement de taille de police
    chargement_police(TAILLE_POLICE_T1);
    SDL_Surface *text1=TTF_RenderText_Blended(struct_jeu.police,"PEPITE DE FIGHT",couleurBlanc);//�criture du text en gros "T1"

    //changement de taille de police
    chargement_police(TAILLE_POLICE_T4);
    SDL_Surface *text2=TTF_RenderText_Blended(struct_jeu.police,"By GS'corp",couleurBlanc);//�criture du text en moyen "T3"
    SDL_Rect rectDEST_text1= {w*0.15,h*0.33,text1->w,text1->h};
    SDL_Rect rectDEST_text2= {w*0.30,h*0.48,text2->w,text2->h};

    if(SDL_BlitSurface(text1,NULL,surface,&rectDEST_text1))quitter(SDL_BASE);
    if(SDL_BlitSurface(text2,NULL,surface,&rectDEST_text2))quitter(SDL_BASE);
    //On lib�re la m�moire de la texture et on remet la nouvelle
    SDL_DestroyTexture(texture_fond);
    texture_fond=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surface);
    if(texture_fond==NULL)quitter(SDL_BASE);
    //=============
    SDL_SetTextureBlendMode(texture_fond, SDL_BLENDMODE_BLEND);
    //affichage succesif du text
    SDL_Delay(3000);
    for(int i=0; i<70; i++)
    {
        SDL_SetTextureAlphaMod(texture_fond,i);
        if(SDL_RenderCopy(struct_jeu.rendu_fenetre, texture_fond, NULL, NULL))quitter(SDL_BASE);
        SDL_RenderPresent(struct_jeu.rendu_fenetre);
        SDL_Delay(FRAME_RATE_INTRO);
    }
    SDL_FreeSurface(surface);
    SDL_FreeSurface(text1);
    SDL_FreeSurface(text2);
    SDL_DestroyTexture(texture_fond);
}

/**
 * \fn void transition_visuelle()
 * \brief Pour éviter d'avoir un changement brutale de texture, cette fonction "noirci" la texture afin de réaliser une transition correcte
*/
void transition_visuelle()
{
    SDL_Surface *surface=SDL_GetWindowSurface(struct_jeu.fenetre_jeu);
    if(surface==NULL)quitter(SDL_BASE);
    SDL_DestroyTexture(struct_jeu.transition);
    struct_jeu.transition=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surface);
    SDL_FreeSurface(surface);
    SDL_SetTextureBlendMode(struct_jeu.transition, SDL_BLENDMODE_BLEND);
    for(int i=0; i<10; i++)
    {
        SDL_SetTextureAlphaMod(struct_jeu.transition,(10-i)*10);
        if(SDL_RenderCopy(struct_jeu.rendu_fenetre, struct_jeu.transition, NULL, NULL))quitter(SDL_BASE);
        SDL_RenderPresent(struct_jeu.rendu_fenetre);
        SDL_Delay(FRAME_TRANSITION);
    }
}

/**
 * \fn void affichage_accueil()
 * \brief Cette fonction affiche le la vidéo en arrière plan ainsi que le menu de l'accueil
*/
void affichage_accueil()
{
    //cette fonction affiche une image de la vid�o de fond puis l'accueil
    if(struct_jeu.textures_fond_accueil[struct_jeu.frequence_video]!=NULL)
    {
        SDL_RenderCopy(struct_jeu.rendu_fenetre,struct_jeu.textures_fond_accueil[struct_jeu.frequence_video++],NULL,NULL);
        struct_jeu.frequence_video++;
        struct_jeu.frequence_video%=100;
    }
    SDL_RenderCopy(struct_jeu.rendu_fenetre,struct_jeu.texture_accueil,NULL,NULL);
}
