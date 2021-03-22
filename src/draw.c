/**
 * @file        draw.c
 * @brief       Contient toutes les fonctions en rapport avec l'affichage
 * @author      Meunier Rodrigue Nicolas Lemoult Mathis Morisseau
 * @version     1.0
 * @date        2021
 * @copyright   Le Mans Université
 */

#include "../include/draw.h"
SDL_Color couleurBlanc  =   {255,255,255,255};
SDL_Color couleurBleu   =   {0, 0, 255, 255};
SDL_Color couleurOrange =   {255, 140, 40, 255};
SDL_Color couleurVert   =   {0, 255, 0, 255};
SDL_Color couleurJaune  =   {255, 255, 0, 255};
SDL_Color couleurRose   =   {255, 110, 137, 255};
SDL_Color couleurRouge  =   {255, 0, 0, 255};
SDL_Color couleurNoir   =   {0, 0, 0, 255};
const float tab_rapport[4] = {RAPPORT_X_J1_VIE,RAPPORT_X_J2_VIE,RAPPORT_X_J3_VIE,RAPPORT_X_J4_VIE};
const uint32_t tab_mapRGB[4][3] =
{
    {255,    0,      0},
    {255,    255,    0},
    {0,      0,      255},
    {0,      255,    0}
};

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
    char *chaine=NULL;
    chaine=malloc(strlen(SRC_IMG_PARA)*sizeof(char));
    strcpy(chaine,SRC_IMG_PARA);
    for(int i=0; i<3; i++)
    {
        surf=IMG_Load(chaine);
        if(surf == NULL)quitter(SDL_IMAGE);
        chaine[9]++;// cette ligne permet d'incr�menter le num�ro de l'image '1'.png
        jeu_parametres.tabMenu[i]=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
        SDL_FreeSurface(surf);
    }
    jeu_parametres.page=0;
    if(chaine != NULL)free(chaine);

    //Cr�ation textures d'arri�re plan jeu
    chaine=malloc(strlen(SRC_IMG_JEU)*sizeof(char));
    strcpy(chaine,SRC_IMG_JEU);
    for(int i=0; i<NB_IMG_FOND; i++)
    {
        chaine[17]++;// cette ligne permet d'incr�menter le num�ro de l'image '1'.png
        surf=IMG_Load(chaine);
        if(surf == NULL)quitter(SDL_IMAGE);
        struct_jeu.textures_fond_jeu[i]=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
        SDL_FreeSurface(surf);
    }
    free(chaine);

    //Cr�ation textures du plateau du jeu
    chaine=malloc(strlen(SRC_IMG_PLATEAU)*sizeof(char));
    strcpy(chaine,SRC_IMG_PLATEAU);
    for(int i=1; i<NB_IMG_PLATEAU+1; i++)
    {
        surf=IMG_Load(chaine);
        if(surf == NULL)quitter(SDL_IMAGE);
        chaine[20]++;// cette ligne permet d'incr�menter le num�ro de l'image '1'.png
        struct_jeu.textures_plateau_jeu[i-1]=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
        SDL_FreeSurface(surf);
    }
    free(chaine);
}
/**
 * \fn void recharger_Texture(SDL_Texture **texture,char *source)
 * \brief Pour éviter d'avoir à un instant T toutes les textures de chargée et une utilisation Ram beaucoup trop élévée, le programme va décharger les textures, cette fonction recharge une texture
*/
void recharger_Texture(SDL_Texture **texture,char *source)
{
    if(*texture != NULL)SDL_DestroyTexture(*texture);
    SDL_Surface *surface=IMG_Load(source);
    if(surface==NULL)quitter(SDL_IMAGE);
    (*texture)=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surface);
    SDL_FreeSurface(surface);
}
/**
 * \fn void decharger_Texture(SDL_Texture **texture)
 * \brief Pour éviter d'avoir à un instant T toutes les textures de chargée et une utilisation Ram beaucoup trop élévée, le programme va décharger les textures, cette fonction décharge la texture qui lui est passée
*/
void decharger_Texture(SDL_Texture **texture)
{
    if(*texture != NULL)SDL_DestroyTexture(*texture);
    *texture=NULL;
    if(*texture != NULL)quitter(SDL_BASE);
}
/**
 * \fn void creation_textures_personnage()
 * \brief Cette fonction créer les textures en fonction du choix du joueur sur son personnage
 * \param 1 si on ne veut charger que les textures idle pour choix personnage
*/
void creation_textures_personnage()
{
    SDL_Surface *surf=NULL;
    char *chaine=NULL;
    for(int i=0; i<struct_jeu.nombre_joueurs; i++)
    {
        switch(struct_jeu.joueurs[i].type_personnage/10)
        {
        case CHEVALIER:
            chaine=malloc(sizeof(char)*strlen(SRC_IMG_PERSONNAGE_CHEVALIER));
            strcpy(chaine,SRC_IMG_PERSONNAGE_CHEVALIER);
            chaine[26]='0'+((struct_jeu.joueurs[i].type_personnage)%10);
            for(int y=0; y<6; y++)
                for(int z=0; z<10; z++)
                {
                    chaine[28]='0'+y;
                    chaine[30]='0'+z;
                    surf=IMG_Load(chaine);
                    if(surf==NULL)quitter(SDL_IMAGE);
                    struct_jeu.textures_personnages_joueurs[i][y][z]=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
                    SDL_FreeSurface(surf);
                }
            break;
        case ELFE:
            chaine=malloc(sizeof(char)*strlen(SRC_IMG_PERSONNAGE_ELFE));
            strcpy(chaine,SRC_IMG_PERSONNAGE_ELFE);
            chaine[21]='0'+(struct_jeu.joueurs[i].type_personnage)%10;
            for(int y=0; y<6; y++)
                for(int z=0; z<10; z++)
                {
                    chaine[23]='0'+y;
                    chaine[25]='0'+z;
                    surf=IMG_Load(chaine);
                    if(surf==NULL)quitter(SDL_IMAGE);
                    struct_jeu.textures_personnages_joueurs[i][y][z]=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
                    SDL_FreeSurface(surf);
                }
            if((struct_jeu.joueurs[i].type_personnage)%10 != 2)
            {
                free(chaine);
                chaine=malloc(sizeof(char)*strlen(SRC_IMG_PERSONNAGE_ELFE_FLECHE));
                chaine[22]='0'+(struct_jeu.joueurs[i].type_personnage)%10;
                surf=IMG_Load(chaine);
                if(surf != NULL)
                {
                    quitter(SDL_IMAGE);
                }
                struct_jeu.joueurs[i].fleche=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
                SDL_FreeSurface(surf);

            }
            break;
        case FEE:
            chaine=malloc(sizeof(char)*strlen(SRC_IMG_PERSONNAGE_FEE));
            strcpy(chaine,SRC_IMG_PERSONNAGE_FEE);
            chaine[20]='0'+(struct_jeu.joueurs[i].type_personnage)%10;
            for(int y=0; y<6; y++)
                for(int z=0; z<10; z++)
                {
                    chaine[22]='0'+y;
                    chaine[24]='0'+z;
                    surf=IMG_Load(chaine);
                    if(surf==NULL)quitter(SDL_IMAGE);
                    struct_jeu.textures_personnages_joueurs[i][y][z]=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
                    SDL_FreeSurface(surf);
                }
            free(chaine);
            chaine=malloc(sizeof(char)*strlen(SRC_IMG_PERSONNAGE_FEE_FLECHE));
            chaine[20]='0'+(struct_jeu.joueurs[i].type_personnage)%10;
            surf=IMG_Load(chaine);
            if(surf != NULL)
            {
                quitter(SDL_IMAGE);
            }
            struct_jeu.joueurs[i].fleche=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
            SDL_FreeSurface(surf);
            break;
        case WARRIOR:
            chaine=malloc(sizeof(char)*strlen(SRC_IMG_PERSONNAGE_WARRIOR));
            strcpy(chaine,SRC_IMG_PERSONNAGE_WARRIOR);
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
            surf=IMG_Load(SRC_IMG_PERSONNAGE_WARRIOR_FLECHE);
            if(surf != NULL)
            {
                struct_jeu.joueurs[i].fleche=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surf);
                SDL_FreeSurface(surf);
            }
            break;
        }
        free(chaine);

    }
    if(struct_jeu.nombre_joueurs)
    {
        if(struct_jeu.nombre_joueurs==2)surf=IMG_Load(SRC_IMG_VIE2J);
        else surf=IMG_Load(SRC_IMG_VIE4J);
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
            {
                if(struct_jeu.textures_personnages_joueurs[i][j][k] != NULL)SDL_DestroyTexture(struct_jeu.textures_personnages_joueurs[i][j][k]);
                struct_jeu.textures_personnages_joueurs[i][j][k]=NULL;
            }
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
        rendre_affichage();
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
    if(struct_jeu.texture_accueil==NULL)recharger_Texture(&(struct_jeu.texture_accueil),SRC_IMG_ACCUEIL);
    SDL_RenderCopy(struct_jeu.rendu_fenetre,struct_jeu.texture_accueil,NULL,NULL);
}

/**
 * \fn void afficher_details_parametres()
 * \brief Selon la page dans les parametres que nous nous trouvons, les informations que dispose le programme doivent être affichés, cette fonction réalise cette tache.
*/
void afficher_details_parametres()
{
    SDL_RenderCopy(struct_jeu.rendu_fenetre,jeu_parametres.tabMenu[jeu_parametres.page],NULL,NULL);
    SDL_Surface *text=NULL;
    SDL_Surface *surfaceDest=SDL_CreateRGBSurface(0, 1920, 1080, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
    SDL_Rect Rectangle= {0,0,0,0};
    SDL_Texture *texture=NULL;
    //changement de taille de police
    chargement_police(TAILLE_POLICE_T55);
    char chaine[20];
    memset(chaine,0,sizeof(char)*20);
    switch(jeu_parametres.page)
    {
    case PAGE_GRAPHISMES:

        sprintf(chaine,"%d / %d", jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution],jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]);//on convertit en chaine de caract�re la r�solution acctuelle
        text=TTF_RenderText_Blended(struct_jeu.police,chaine,couleurBlanc);//Appel de la fonction TTF_RenderText pour transformer la "chaine" en surface SDL
        Rectangle.x=XRAPPORT_PARA_RE*1920;
        Rectangle.y=YRAPPORT_PARA_RE*1080;
        Rectangle.h=text->h;
        Rectangle.w=text->w;
        SDL_BlitSurface(text,NULL,surfaceDest,&Rectangle);//on blit la surface text qui contient la r�solution
        SDL_FreeSurface(text);
        if(jeu_parametres.mode)strcpy(chaine,"Plein Ecran");
        else strcpy(chaine,"Fenetre");

        text=TTF_RenderText_Blended(struct_jeu.police,chaine,couleurBlanc);
        Rectangle.x=XRAPPORT_PARA_MA*1920;
        Rectangle.y=YRAPPORT_PARA_MA*1080;
        Rectangle.h=text->h;
        Rectangle.w=text->w;
        SDL_BlitSurface(text,NULL,surfaceDest,&Rectangle);//on blit la surface text qui contient le mode d'affichage
        SDL_FreeSurface(text);

        sprintf(chaine,"%d", jeu_parametres.plageFPS[jeu_parametres.fps]);//on convertit en chaine de caractère les fps max
        text=TTF_RenderText_Blended(struct_jeu.police,chaine,couleurBlanc);
        Rectangle.x=XRAPPORT_PARA_FPS*1920;
        Rectangle.y=YRAPPORT_PARA_FPS*1080;
        Rectangle.h=text->h;
        Rectangle.w=text->w;
        SDL_BlitSurface(text,NULL,surfaceDest,&Rectangle);//on blit la surface text qui contient les fps


        if(jeu_parametres.affichFPS)
        {
            SDL_FreeSurface(text);
            text=IMG_Load(SRC_IMG_CHECK);
            Rectangle.x=2+XRAPPORT_BOUTON_AFPS*1920;
            Rectangle.y=2+YRAPPORT_BOUTON_AFPS*1080;
            Rectangle.h=text->h;
            Rectangle.w=text->w;
            SDL_BlitSurface(text,NULL,surfaceDest,&Rectangle);//on blit la surface text qui contient l'image check pour montrer a l'utilisateur que le programme affiche les fps
        }
        texture=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surfaceDest);
        if(texture==NULL)quitter(SDL_BASE);
        SDL_RenderCopy(struct_jeu.rendu_fenetre,texture,NULL,NULL);
        SDL_FreeSurface(text);
        SDL_DestroyTexture(texture);


        break;
    /*
    case PAGE_PLATEAU:
    Rectangle.x=XRAPPORT_APERCU_PLAT*jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution];
    Rectangle.y=YRAPPORT_APERCU_PLAT*jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution];
    Rectangle.h=4+HRAPPORT_APERCU_PLAT*jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution];
    Rectangle.w=2+LRAPPORT_APERCU_PLAT*jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution];
    SDL_RenderCopy(struct_jeu.rendu_fenetre,struct_jeu.textures_fond_jeu[struct_jeu.texture_plateau_jeu_selectione],NULL,&Rectangle);
    SDL_RenderCopy(struct_jeu.rendu_fenetre,struct_jeu.textures_plateau_jeu[struct_jeu.texture_plateau_jeu_selectione],NULL,&Rectangle);
    break;
    */
    case PAGE_AUDIO:
        //pour la musique
        Rectangle.x=1+XRAPPORT_CUR_MUS*1920;
        Rectangle.y=1+YRAPPORT_CUR_MUS*1080;
        Rectangle.h=(YMAXRAPPORT_CUR_MUS*1080-YRAPPORT_CUR_MUS*1080);
        Rectangle.w=(jeu_parametres.musique*0.01)*(int)((XMAXRAPPORT_CUR_MUS-XRAPPORT_CUR_MUS)*1920);
        SDL_FillRect(surfaceDest,&Rectangle,SDL_MapRGB(surfaceDest->format, 41, 238, 205));
        //pour les effets sonores
        Rectangle.x=1+XRAPPORT_CUR_EFS*1920;
        Rectangle.y=1+YRAPPORT_CUR_EFS*1080;
        Rectangle.h=(YMAXRAPPORT_CUR_EFS*1080-YRAPPORT_CUR_EFS*1080);
        Rectangle.w=(jeu_parametres.effets*0.01)*(int)((XMAXRAPPORT_CUR_EFS-XRAPPORT_CUR_EFS)*1920);
        SDL_FillRect(surfaceDest,&Rectangle,SDL_MapRGB(surfaceDest->format, 41, 238, 205));
        //pour les dialogues
        Rectangle.x=1+XRAPPORT_CUR_DIA*1920;
        Rectangle.y=1+YRAPPORT_CUR_DIA*1080;
        Rectangle.h=(YMAXRAPPORT_CUR_DIA*1080-YRAPPORT_CUR_DIA*1080);
        Rectangle.w=(jeu_parametres.dialogues*0.01)*(int)((XMAXRAPPORT_CUR_DIA-XRAPPORT_CUR_DIA)*1920);
        SDL_FillRect(surfaceDest,&Rectangle,SDL_MapRGB(surfaceDest->format, 41, 238, 205));

        if(jeu_parametres.arriere_plan)
        {
            text=IMG_Load(SRC_IMG_CHECK);
            Rectangle.x=2+XRAPPORT_BOUTON_SAP*1920;
            Rectangle.y=2+YRAPPORT_BOUTON_SAP*1080;
            Rectangle.h=text->h;
            Rectangle.w=text->w;
            SDL_BlitSurface(text,NULL,surfaceDest,&Rectangle);//on blit la surface text qui contient l'image check pour montrer � l'utilisateur que le programme affiche les fps
            SDL_FreeSurface(text);
        }
        texture=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,surfaceDest);
        if(texture==NULL)quitter(SDL_BASE);
        SDL_RenderCopy(struct_jeu.rendu_fenetre,texture,NULL,NULL);
        SDL_DestroyTexture(texture);
        break;
    case PAGE_CONTROLES:
        break;
    }
    SDL_FreeSurface(surfaceDest);

}
/**
 * \fn void affichage_fps()
 * \brief Comme dans tous jeu de "baston" on peut être ammené à quel fréquence le programme "tourne", cette fonction affiche les fps moyen, min et max si le joueur à choisi de les afficher
*/
void affichage_fps()
{
    if(jeu_parametres.affichFPS)
    {
        if(struct_jeu.frames_evolution%FREC_AFFICHAGE_FPS || struct_jeu.texture_fps==NULL)
        {
            char chaine[20];
            sprintf(chaine,"FPS:%d, max:%d min:%d",struct_jeu.fpsMoy,struct_jeu.fpsMax,struct_jeu.fpsMin);
            //changement de taille de police
            chargement_police(TAILLE_POLICE_T8);
            SDL_FreeSurface(struct_jeu.surface_fps);
            SDL_DestroyTexture(struct_jeu.texture_fps);
            struct_jeu.surface_fps=TTF_RenderText_Solid(struct_jeu.police,chaine,couleurBlanc);
            struct_jeu.texture_fps=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,struct_jeu.surface_fps);
        }
        SDL_Rect position= {0,0,struct_jeu.surface_fps->w,struct_jeu.surface_fps->h};
        SDL_RenderCopy(struct_jeu.rendu_fenetre,struct_jeu.texture_fps,NULL,&position);
    }
}
/**
 * \fn void rendre_affichage()
 * \brief Pour éviter de se mélanger les pinceaux, cette fonction réalise l'affichage du rendu, comme en SDL les textures sont superposées comme des calques, cette fonction affichera le sommet du calque
 */
void rendre_affichage()
{
    SDL_RenderPresent(struct_jeu.rendu_fenetre);
}
/**
 * \fn void afficher_partie()
 * \brief Cette fonction affiche le fond d'écran de la partie ainsi que les plateformes, celles ci sont sélectionnées dans les paramêtres
 */
void afficher_partie()
{
    /*Pour l'instant la fonction fait juste render_copy mais � l'avenir cette fonction calculera la surface de la texture � afficher
     *
     */
    SDL_RenderCopy(struct_jeu.rendu_fenetre,struct_jeu.textures_fond_jeu[struct_jeu.texture_plateau_jeu_selectione],NULL,NULL);
    SDL_RenderCopy(struct_jeu.rendu_fenetre,struct_jeu.textures_plateau_jeu[struct_jeu.texture_plateau_jeu_selectione],NULL,NULL);
}

/**
 * \fn void afficher_joueurs()
 * \brief En fonction des textures séléctionnées par le joueur, le programme durant la partie va afficher les joueurs grâce à cette fonction
 */
void afficher_joueurs()
{
    SDL_Rect position_Final= {0,0,(int)(jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*RAPPORT_LARGEUR_PERSO),(int)(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*RAPPORT_HAUTEUR_PERSO)};
    SDL_RendererFlip flip = SDL_FLIP_VERTICAL;
    for(int i=0; i<struct_jeu.nombre_joueurs; i++)
    {
        position_Final.x=((struct_jeu.joueurs[i].positionX)*(jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution])/1920)-jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*RAPPORT_OFFSET_X;
        position_Final.y=((struct_jeu.joueurs[i].positionY)*(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution])/1080)-jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*RAPPORT_OFFSET_Y;

        position_Final.h=(int)(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*RAPPORT_Y_PERSO);
        position_Final.w=(int)(jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution]*RAPPORT_X_PERSO);
        if(struct_jeu.joueurs[i].direction==DROITE)
        {
            if(SDL_RenderCopy(struct_jeu.rendu_fenetre,struct_jeu.textures_personnages_joueurs[i][struct_jeu.joueurs[i].etat][struct_jeu.frames_evolution%10],NULL,&position_Final) <0)quitter(SDL_BASE);
        }
        else
        {
            if(SDL_RenderCopyEx(struct_jeu.rendu_fenetre,struct_jeu.textures_personnages_joueurs[i][struct_jeu.joueurs[i].etat][struct_jeu.frames_evolution%10],NULL,&position_Final,180,NULL,flip) <0)quitter(SDL_BASE);
        }
    }
}

/**
 * \fn void afficher_vie_joueurs()
 * \brief Les personnages ont une bare de vie, donc à tout moment le joueur est ammené à savoir combien de vie a son personnage, cette fonction affiche à l'écran la vie de tous les joueurs
*/
void afficher_vie_joueurs()
{
    if(struct_jeu.texture_rect_vie == NULL || struct_jeu.perte_vie==1)
    {
        struct_jeu.perte_vie=0;
        SDL_Rect Rectangle= {0,Y_VIE,0,H_VIE};
        if(struct_jeu.rectangle_vie!=NULL)SDL_FreeSurface(struct_jeu.rectangle_vie);
        struct_jeu.rectangle_vie=SDL_CreateRGBSurface(0, 1920, 1080, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
        for(int i=0; i<struct_jeu.nombre_joueurs; i++)
        {
            Rectangle.x=tab_rapport[i]*1920;
            Rectangle.w=((RAPPORT_W_VIE*1920)/100)*struct_jeu.joueurs[i].vie;
            SDL_FillRect(struct_jeu.rectangle_vie,&Rectangle,SDL_MapRGB(struct_jeu.rectangle_vie->format,tab_mapRGB[i][R],tab_mapRGB[i][G],tab_mapRGB[i][B]));
        }
        if(struct_jeu.texture_rect_vie!=NULL)SDL_DestroyTexture(struct_jeu.texture_rect_vie);
        struct_jeu.texture_rect_vie=SDL_CreateTextureFromSurface(struct_jeu.rendu_fenetre,struct_jeu.rectangle_vie);
    }
    SDL_RenderCopy(struct_jeu.rendu_fenetre,struct_jeu.vie_joueurs,NULL,NULL);
    SDL_RenderCopy(struct_jeu.rendu_fenetre,struct_jeu.texture_rect_vie,NULL,NULL);
}
/**
 * \fn void afficher_ecran_multijoueur()
 * \brief Une fois le mode multijoueur séléctionné, le joueur est ammené à selectionner un mode "2j/4J :: local / réseau", cette fonction affiche à l'écran des cases où cliquer pour selectionner ce mode
 */
void afficher_ecran_multijoueur()
{
    if(struct_jeu.texture_multijoueur==NULL)recharger_Texture(&(struct_jeu.texture_multijoueur),SRC_IMG_MULTI);
    SDL_RenderCopy(struct_jeu.rendu_fenetre,struct_jeu.texture_multijoueur,NULL,NULL);
}

/**
 * \fn void afficher_pause()
 * \brief Si le(s) joueur(s) est(sont) en local, il y a la possibilité de mettre pause, cette fonction affiche le menu pause
 */
void afficher_pause()
{
}

/**
 * \fn void modifier_window()
 * \brief Lorsque l'utilisateur est dans les paramètres du jeu, il peut être ammené à modifier la taille de sa fenêtre, cette fonction regroupe toutes les fonctions réalisant ce changement
 */
void modifier_window()
{
    if(jeu_parametres.mode)
    {
        SDL_SetWindowFullscreen(struct_jeu.fenetre_jeu,SDL_WINDOW_FULLSCREEN_DESKTOP);
        SDL_GetWindowSize(struct_jeu.fenetre_jeu,&jeu_parametres.reso[0][9],&jeu_parametres.reso[1][9]);
    }
    else
    {
        SDL_SetWindowFullscreen(struct_jeu.fenetre_jeu,SDL_WINDOW_SHOWN);
        SDL_SetWindowSize(struct_jeu.fenetre_jeu,jeu_parametres.reso[0][jeu_parametres.resolution], jeu_parametres.reso[1][jeu_parametres.resolution]);
        SDL_SetWindowPosition(struct_jeu.fenetre_jeu,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
    }
}

/**
 * \fn void affiche_choix_personnages(int *tab)
 * \brief Cette fonction permet d'afficher le selecteur qui rend compte de quels personnages les joueurs sont ammenés à jouer
 */
void affiche_choix_personnages(int *tab)
{
    if(struct_jeu.selection_personnages==NULL)recharger_Texture(&(struct_jeu.selection_personnages),SRC_IMG_CHOIX_PERSONNAGE);
    SDL_RenderCopy(struct_jeu.rendu_fenetre,struct_jeu.selection_personnages,NULL,NULL);
    SDL_Rect position= {0,0,RAPPORT_L_SELEC*jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution],RAPPORT_H_SELEC*jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]};
    int y;
    if(struct_jeu.selecteur==NULL)recharger_Texture(&(struct_jeu.selecteur),SRC_IMG_SELECTEUR);
    for(int i=0; i<struct_jeu.nombre_joueurs; i++)
    {
        y=tab[i];
        position.x=RAPPORT_XMIN_SELEC*jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution];
        while(y>=3)
        {
            y-=3;
            position.x+=RAPPORT_PAS_X_SELEC*jeu_parametres.reso[0][jeu_parametres.mode?9:jeu_parametres.resolution];
        }
        position.y=(RAPPORT_YMIN_SELEC+y*RAPPORT_PAS_Y_SELEC)*jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution];
        switch(i)
        {
        case J1:
            SDL_SetTextureColorMod(struct_jeu.selecteur,255,0,0);
            break;
        case J2:
            SDL_SetTextureColorMod(struct_jeu.selecteur,255,255,0);
            break;
        case J3:
            SDL_SetTextureColorMod(struct_jeu.selecteur,0,0,255);
            break;
        case J4:
            SDL_SetTextureColorMod(struct_jeu.selecteur,0,255,0);
            break;
        }
        SDL_RenderCopy(struct_jeu.rendu_fenetre,struct_jeu.selecteur,NULL,&position);
    }
}

