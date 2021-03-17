/**
 * @file        sounds.h
 * @brief       Contient les déclarations des fonctions de son
 * @author      Meunier Rodrigue Nicolas Lemoult Mathis Morisseau
 * @version     1.0
 * @date        2021
 * @copyright   Le Mans Université
 */
#ifndef __SOUNDS__
#define __SOUNDS__

#include "struct.h"

void creation_canaux_musique();
void chargement_musique(int channel, int extra,int rep);
void changement_volumes_musiques();
void detruire_musique(int extra);










#endif // __SOUNDS__
