/**
 * @file        sockets.h
 * @brief       Contient les déclarations des fonctions liées au réseau
 * @author      Meunier Rodrigue Nicolas Lemoult Mathis Morisseau
 * @version     1.0
 * @date        2021
 * @copyright   Le Mans Université
 */
#ifndef __SOCKETS__
#define __SOCKETS__

#include "struct.h"

/*  FONCTIONS   */
void initialisation_socket();
int hostname_to_ip(char * hostname, char* ip);
void creation_socket(char *hostname);
void connexion_client();
void lire_socket();
void ecrire_socket();
void destruction_socket();


#endif // __SOCKETS__
