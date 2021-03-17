/**
 * @file        init.h
 * @brief       Contient les déclarations des fonctions d'initialisation
 * @author      Meunier Rodrigue Nicolas Lemoult Mathis Morisseau
 * @version     1.0
 * @date        2021
 * @copyright   Le Mans Université
 */
#ifndef __INIT__
#define __INIT__

#include "struct.h"




/*      FONCTIONS       */
void initialisation_Textures();
void initialisation_parametres();
void chargement_police(int taille);
void chargement_parametres();
void sauvegarde_parametres();
void quitter(int code);
void write_all_varia();








#endif // __INIT__
