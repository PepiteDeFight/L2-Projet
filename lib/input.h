/**
 * @file        input.h
 * @brief       Contient les déclarations des fonctions d'événements
 * @author      Meunier Rodrigue Nicolas Lemoult Mathis Morisseau
 * @version     1.0
 * @date        2021
 * @copyright   Le Mans Université
 */
#ifndef __INPUT__
#define __INPUT__

#include "struct.h"
int input_popup();
void accueil();
void menu_parametre();
void campagne();
int multijoueur();
void partie();
int choix_serveur();
int choix_personnages();
int choix_plateau();
void jeu_pause();
void changement_control(int control, int joueur);
void ignorer_event();
void retablir_event();
void victoire(int equipe);





#endif // __INPUT__
