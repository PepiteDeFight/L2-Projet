/**
 * @file        input.c
 * @brief       Contient l'implémentation des fonctions d'événements ainsi que de jeu
 * @author      A changer
 * @version     1.0
 * @date        2021
 * @copyright   Le Mans Université
 */
#include "include/input.h"
/**
 * \fn int input_popup()
 * \brief Cette fonction gère l'entrée des événements de la popup d'erreur, dans le cas où une erreur survient (cf : quitter() -> init.c)
 *
 * \return RETOUR_QUITTER si l'utilisateur veut mettre fin au programme ou RETOUR_POURSUIVRE s'il souhaite poursuivre malgré l'erreur
 */
