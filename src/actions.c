/**
 * @file        actions.c
 * @brief       Contient l'implementation des fonctions en rapport avec les deplacements des personnages.
 * @author      Meunier Rodrigue Nicolas Lemoult Mathis Morisseau
 * @version     1.0
 * @date        2021
 * @copyright   Le Mans Université
 */
#include "../include/actions.h"

/**
 * \fn void pesanteur()
 * \brief Cette fonction applique de la gravité au joueur pour rendre le jeu plus réaliste
 *
 */
void pesanteur()
{
    for(int i=0; i<struct_jeu.nombre_joueurs; i++)
    {
        if(!(struct_jeu.joueurs[i].positionY==RCT_Y_1 && struct_jeu.joueurs[i].positionX>=RCT_X_1 && struct_jeu.joueurs[i].positionX<=RCT_XMAX_1) && !(struct_jeu.joueurs[i].positionY==RCT_Y_2 && struct_jeu.joueurs[i].positionX>=RCT_X_2 && struct_jeu.joueurs[i].positionX<=RCT_XMAX_2) && !(struct_jeu.joueurs[i].positionY==RCT_Y_3 && struct_jeu.joueurs[i].positionX>=RCT_X_3 && struct_jeu.joueurs[i].positionX<=RCT_XMAX_3) && !(struct_jeu.joueurs[i].positionY==RCT_Y_4 && struct_jeu.joueurs[i].positionX>=RCT_X_4 && struct_jeu.joueurs[i].positionX<=RCT_XMAX_4) && struct_jeu.frames_evolution%FREQ_CHUTE && struct_jeu.joueurs[i].etat!=JUMP)
        {
            struct_jeu.joueurs[i].positionY+=GRAVITE;
            if(struct_jeu.joueurs[i].positionY<=RCT_Y_1+GRAVITE && struct_jeu.joueurs[i].positionY>RCT_Y_1 && struct_jeu.joueurs[i].positionX>=RCT_X_1 && struct_jeu.joueurs[i].positionX<=RCT_XMAX_1 )//cas de la plus basse plateforme
            {
                struct_jeu.joueurs[i].positionY-=struct_jeu.joueurs[i].positionY-RCT_Y_1;//on soustrait la différence
            }
            else
            {
                if (struct_jeu.joueurs[i].positionY<=RCT_Y_2+GRAVITE && struct_jeu.joueurs[i].positionY>RCT_Y_2 && struct_jeu.joueurs[i].positionX>=RCT_X_2 && struct_jeu.joueurs[i].positionX<=RCT_XMAX_2)
                {
                    struct_jeu.joueurs[i].positionY-=struct_jeu.joueurs[i].positionY-RCT_Y_2;//on soustrait la différence
                }
                else
                {
                    if (struct_jeu.joueurs[i].positionY<=RCT_Y_3+GRAVITE && struct_jeu.joueurs[i].positionY>RCT_Y_3 && struct_jeu.joueurs[i].positionX>=RCT_X_3 && struct_jeu.joueurs[i].positionX<=RCT_XMAX_3)
                    {
                        struct_jeu.joueurs[i].positionY-=struct_jeu.joueurs[i].positionY-RCT_Y_3;//on soustrait la différence
                    }
                    else
                    {
                        if(struct_jeu.joueurs[i].positionY<=RCT_Y_4+GRAVITE && struct_jeu.joueurs[i].positionY>RCT_Y_4 && struct_jeu.joueurs[i].positionX>=RCT_X_4 && struct_jeu.joueurs[i].positionX<=RCT_XMAX_4)
                        {
                            struct_jeu.joueurs[i].positionY-=struct_jeu.joueurs[i].positionY-RCT_Y_4;//on soustrait la différence
                        }
                    }
                }

            }
        }
    }
}
/**
 * \fn void avancer()
 * \brief La fonction avancer permet de sois faire avancer sois faire reculer les joueurs si leur évent respectifs sont à 1 struct_jeu.tableau_event (cf struct.h)
 *
 */
void avancer()
{
    for(int i=J1; i<J4; i++)
    {
        if(struct_jeu.tableau_event[i][0])
        {
            if(i%2)
            {
                struct_jeu.joueurs[i].direction=GAUCHE;
                struct_jeu.joueurs[i].positionX-=3;
            }
            else
            {
                struct_jeu.joueurs[i].direction=DROITE;
                struct_jeu.joueurs[i].positionX+=3;
            }

            struct_jeu.joueurs[i].etat=WALK;
            struct_jeu.joueurs[i].modification=1;
        }
        if(struct_jeu.tableau_event[i][1])
        {
            if(i%2)
            {
                struct_jeu.joueurs[i].direction=DROITE;
                struct_jeu.joueurs[i].positionX+=3;
            }
            else
            {
                struct_jeu.joueurs[i].direction=GAUCHE;
                struct_jeu.joueurs[i].positionX-=3;
            }
            struct_jeu.joueurs[i].etat=WALK;
            struct_jeu.joueurs[i].modification=1;
        }
    }
}
/**
 * \fn void sauter()
 * \brief Cette fonction permet de faire sauter le joueur
 *
 */
void sauter()
{
    for(int i=J1; i<J4; i++)
    {
        /*if(struct_jeu.tableau_event[i][2]) struct_jeu.joueurs[i].jump++;
        if(struct_jeu.joueurs[i].jump>=60){
            struct_jeu.joueurs[i].jump=0;
            struct_jeu.joueurs[i].modification=0;
        }

        if(struct_jeu.joueurs[i].jump && struct_jeu.frames_evolution%FREQ_JUMP)
        {
            struct_jeu.joueurs[i].positionY-=16;
            struct_jeu.joueurs[i].etat=JUMP;
            struct_jeu.joueurs[i].modification=1;
            struct_jeu.joueurs[i].jump+=2;
        }
        if((struct_jeu.joueurs[i].positionY==RCT_Y_1 && struct_jeu.joueurs[i].positionX>=RCT_X_1 && struct_jeu.joueurs[i].positionX<=RCT_XMAX_1) || (struct_jeu.joueurs[i].positionY==RCT_Y_2 && struct_jeu.joueurs[i].positionX>=RCT_X_2 && struct_jeu.joueurs[i].positionX<=RCT_XMAX_2) || (struct_jeu.joueurs[i].positionY==RCT_Y_3 && struct_jeu.joueurs[i].positionX>=RCT_X_3 && struct_jeu.joueurs[i].positionX<=RCT_XMAX_3) || (struct_jeu.joueurs[i].positionY==RCT_Y_4 && struct_jeu.joueurs[i].positionX>=RCT_X_4 && struct_jeu.joueurs[i].positionX<=RCT_XMAX_4))
            struct_jeu.joueurs[i].jump=0;
        */
        if(struct_jeu.tableau_event[i][2]) struct_jeu.joueurs[i].positionY-=10;
    }
}
/**
 * \fn void attaquer()
 * \brief Cette fonction permet de faire attaquer le joueur et vérifie si un joueur est présent pour lui infliger des dégats
 *
 */
void attaquer()
{
    for(int i=J1; i<J4; i++)
    {

        if(struct_jeu.tableau_event[i][3])
        {
            struct_jeu.joueurs[i].etat=ATTACK;
            struct_jeu.joueurs[i].modification=1;
            write_all_varia();
            switch(struct_jeu.joueurs[i].type_personnage/10)
            {
            case CHEVALIER:
                if(i%2) //Si i est soit le joueur 2 soit le 4 (0-1-2-3) 2 et 4 correspondent à 1 et 3 soit i%2=1
                {


                    if((struct_jeu.joueurs[J1].positionX < struct_jeu.joueurs[i].positionX+(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J1].positionX > struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==DROITE) || (struct_jeu.joueurs[J1].positionX > struct_jeu.joueurs[i].positionX-(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J1].positionX < struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==GAUCHE))
                    {
                        struct_jeu.joueurs[J1].etat=HURT;
                        if(!(struct_jeu.frames_evolution%FREQ_ATTAQUE))
                        {
                            struct_jeu.joueurs[J1].vie-=DEGATS;
                            struct_jeu.perte_vie=1;
                        }
                    }
                    if(struct_jeu.nombre_joueurs>2)if((struct_jeu.joueurs[J3].positionX < struct_jeu.joueurs[i].positionX+(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J3].positionX > struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==DROITE) || (struct_jeu.joueurs[J3].positionX > struct_jeu.joueurs[i].positionX-(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J3].positionX < struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==GAUCHE))
                        {
                            struct_jeu.joueurs[J3].etat=HURT;
                            if(!(struct_jeu.frames_evolution%FREQ_ATTAQUE))
                            {
                                struct_jeu.joueurs[J3].vie-=DEGATS;
                                struct_jeu.perte_vie=1;
                            }
                        }
                }
                else
                {
                    if((struct_jeu.joueurs[J2].positionX < struct_jeu.joueurs[i].positionX+(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J2].positionX > struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==DROITE) || (struct_jeu.joueurs[J2].positionX > struct_jeu.joueurs[i].positionX-(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J2].positionX < struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==GAUCHE))
                    {
                        struct_jeu.joueurs[J2].etat=HURT;
                        if(!(struct_jeu.frames_evolution%FREQ_ATTAQUE))
                        {
                            struct_jeu.joueurs[J2].vie-=DEGATS;
                            struct_jeu.perte_vie=1;
                        }
                    }
                    if(struct_jeu.nombre_joueurs>2)if((struct_jeu.joueurs[J4].positionX < struct_jeu.joueurs[i].positionX+(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J4].positionX > struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==DROITE) || (struct_jeu.joueurs[J4].positionX > struct_jeu.joueurs[i].positionX-(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J4].positionX < struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==GAUCHE))
                        {
                            struct_jeu.joueurs[J4].etat=HURT;
                            if(!(struct_jeu.frames_evolution%FREQ_ATTAQUE))
                            {
                                struct_jeu.joueurs[J4].vie-=DEGATS;
                                struct_jeu.perte_vie=1;
                            }
                        }
                }
                break;
            case WARRIOR:
                if(struct_jeu.joueurs[i].type_personnage%10<3)
                {
                    if(i%2) //Si i est soit le joueur 2 soit le 4 (0-1-2-3) 2 et 4 correspondent à 1 et 3 soit i%2=1
                    {
                        if((struct_jeu.joueurs[J1].positionX < struct_jeu.joueurs[i].positionX+(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J1].positionX > struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==DROITE) || (struct_jeu.joueurs[J1].positionX > struct_jeu.joueurs[i].positionX-(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J1].positionX < struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==GAUCHE))
                        {
                            struct_jeu.joueurs[J1].etat=HURT;
                            if(!(struct_jeu.frames_evolution%FREQ_ATTAQUE))
                            {
                                struct_jeu.joueurs[J1].vie-=DEGATS;
                                struct_jeu.perte_vie=1;
                            }
                        }
                        if(struct_jeu.nombre_joueurs>2)if((struct_jeu.joueurs[J3].positionX < struct_jeu.joueurs[i].positionX+(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J3].positionX > struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==DROITE) || (struct_jeu.joueurs[J3].positionX > struct_jeu.joueurs[i].positionX-(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J3].positionX < struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==GAUCHE))
                            {
                                struct_jeu.joueurs[J3].etat=HURT;
                                if(!(struct_jeu.frames_evolution%FREQ_ATTAQUE))
                                {
                                    struct_jeu.joueurs[J3].vie-=DEGATS;
                                    struct_jeu.perte_vie=1;
                                }
                            }
                    }
                    else
                    {
                        if((struct_jeu.joueurs[J2].positionX < struct_jeu.joueurs[i].positionX+(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J2].positionX > struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==DROITE) || (struct_jeu.joueurs[J2].positionX > struct_jeu.joueurs[i].positionX-(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J2].positionX < struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==GAUCHE))
                        {
                            struct_jeu.joueurs[J2].etat=HURT;
                            if(!(struct_jeu.frames_evolution%FREQ_ATTAQUE))
                            {
                                struct_jeu.joueurs[J2].vie-=1;
                                struct_jeu.perte_vie=1;
                            }
                        }
                        if(struct_jeu.nombre_joueurs>2)if((struct_jeu.joueurs[J4].positionX < struct_jeu.joueurs[i].positionX+(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J4].positionX > struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==DROITE) || (struct_jeu.joueurs[J4].positionX > struct_jeu.joueurs[i].positionX-(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J4].positionX < struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==GAUCHE))
                            {
                                struct_jeu.joueurs[J4].etat=HURT;
                                if(!(struct_jeu.frames_evolution%FREQ_ATTAQUE))
                                {
                                    struct_jeu.joueurs[J4].vie-=DEGATS;
                                    struct_jeu.perte_vie=1;
                                }
                            }
                    }
                }
                break;
            case ELFE:
                if(struct_jeu.joueurs[i].type_personnage%10==2)
                {
                    if(i%2) //Si i est soit le joueur 2 soit le 4 (0-1-2-3) 2 et 4 correspondent à 1 et 3 soit i%2=1
                    {
                        if((struct_jeu.joueurs[J1].positionX < struct_jeu.joueurs[i].positionX+(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J1].positionX > struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==DROITE) || (struct_jeu.joueurs[J1].positionX > struct_jeu.joueurs[i].positionX-(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J1].positionX < struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==GAUCHE))
                        {
                            struct_jeu.joueurs[J1].etat=HURT;
                            if(!(struct_jeu.frames_evolution%FREQ_ATTAQUE))
                            {
                                struct_jeu.joueurs[J1].vie-=DEGATS;
                                struct_jeu.perte_vie=1;
                            }
                        }
                        if(struct_jeu.nombre_joueurs>2)if((struct_jeu.joueurs[J3].positionX < struct_jeu.joueurs[i].positionX+(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J3].positionX > struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==DROITE) || (struct_jeu.joueurs[J3].positionX > struct_jeu.joueurs[i].positionX-(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J3].positionX < struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==GAUCHE))
                            {
                                struct_jeu.joueurs[J3].etat=HURT;
                                if(!(struct_jeu.frames_evolution%FREQ_ATTAQUE))
                                {
                                    struct_jeu.joueurs[J3].vie-=DEGATS;
                                    struct_jeu.perte_vie=1;
                                }
                            }
                    }
                    else
                    {
                        if((struct_jeu.joueurs[J2].positionX < struct_jeu.joueurs[i].positionX+(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J2].positionX > struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==DROITE) || (struct_jeu.joueurs[J2].positionX > struct_jeu.joueurs[i].positionX-(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J2].positionX < struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==GAUCHE))
                        {
                            struct_jeu.joueurs[J2].etat=HURT;
                            if(!(struct_jeu.frames_evolution%FREQ_ATTAQUE))
                            {
                                struct_jeu.joueurs[J2].vie-=DEGATS;
                                struct_jeu.perte_vie=1;
                            }
                        }
                        if(struct_jeu.nombre_joueurs>2)if((struct_jeu.joueurs[J4].positionX < struct_jeu.joueurs[i].positionX+(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J4].positionX > struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==DROITE) || (struct_jeu.joueurs[J4].positionX > struct_jeu.joueurs[i].positionX-(jeu_parametres.reso[1][jeu_parametres.mode?9:jeu_parametres.resolution]*PAS_ATTAQUE) && struct_jeu.joueurs[J4].positionX < struct_jeu.joueurs[i].positionX && struct_jeu.joueurs[i].direction==GAUCHE))
                            {
                                struct_jeu.joueurs[J4].etat=HURT;
                                if(!(struct_jeu.frames_evolution%FREQ_ATTAQUE))
                                {
                                    struct_jeu.joueurs[J4].vie-=DEGATS;
                                    struct_jeu.perte_vie=1;
                                }
                            }
                    }
                }
                break;
            case FEE:
                break;
            }
        }
    }
}
/**
 * \fn void repos()
 * \brief Les personnages étant animés, si un joueur est "immobile" le personnage passe en "idle" donc se met au repos, cette fonction permet de faire ce changement
 *
 */
void repos()
{
    for(int i=J1; i<J4; i++)
        if(!struct_jeu.joueurs[i].modification)
            struct_jeu.joueurs[i].etat=IDLE;
}
