/**
 * @file        draw.h
 * @brief       Contient les déclarations des fonctions d'affichage
 * @author      Meunier Rodrigue Nicolas Lemoult Mathis Morisseau
 * @version     1.0
 * @date        2021
 * @copyright   Le Mans Université
 */
#ifndef __DRAW__
#define __DRAW__

#include "struct.h"


/*  FONCTIONS   */
void definir_resolutions();
void chargerTextures();
void recharger_Texture(SDL_Texture **texture,char *source);
void decharger_Texture(SDL_Texture **texture);
void creation_textures_personnage();
void destruction_textures_personnage();
void creation_fenetre();
int creation_popup_erreur(char texte[30]);
void chargement_demarrage();
void transition_visuelle();
void affichage_accueil();
void afficher_details_parametres();
void affichage_fps();
void rendre_affichage();
void afficher_partie();
void afficher_joueurs();
void afficher_vie_joueurs();
void afficher_ecran_multijoueur();
void afficher_pause();
void modifier_window();
void affiche_choix_personnages(int *tab);











#endif // __DRAW__
