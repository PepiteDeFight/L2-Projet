/**
 * @file        sockets.c
 * @brief       Contient l'implémentation des fonctions de réseau pour jouer en multijoueur
 * @author      Meunier Rodrigue Nicolas Lemoult Mathis Morisseau
 * @version     1.0
 * @date        2021
 * @copyright   Le Mans Université
 */
#include "../include/sockets.h"

/**
 * \fn void initialisation_socket()
 * \brief Cette fonction permet d'initialiser les paramètres de la socket
 */
void initialisation_socket()
{
    memset(&(sockets.adresse_serveur),0,sizeof(sockets.adresse_serveur));
    sockets.adresse_serveur.sin_port = htons(30000);
    sockets.adresse_serveur.sin_family = AF_INET;
    sockets.adresse_serveur.sin_addr.s_addr = htonl(INADDR_ANY);
}
/**
 * \fn int hostname_to_ip(char * hostname , char* ip)
 * \brief Cette fonction transforme un hostname en ip "claire" pour le programme
 * return 0 si aucune erreur
 */
int hostname_to_ip(char * hostname, char* ip)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ( (he = gethostbyname( hostname ) ) == NULL)quitter(RESEAU);

    addr_list = (struct in_addr **) he->h_addr_list;

    for(i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(ip, inet_ntoa(*addr_list[i]) );
        return 0;
    }

    return 1;
}

/**
 * \fn void creation_socket(char *hostname)
 * \brief Cette fonction permet de créer la socket qui écouteras sur le réseau les packets de données
 */
void creation_socket(char *hostname)
{
    memset(sockets.buffer,0,sizeof(char)*SIZE_BUFFER);
    char ip[100];
    hostname_to_ip(hostname, ip);
    if ((sockets.socket_serveur =socket(AF_INET,SOCK_STREAM,0))== -1)
        quitter(RESEAU);
    /* bind serveur - socket */
    bind(sockets.socket_serveur,(struct sockaddr *)&sockets.adresse_serveur,sizeof(sockets.adresse_serveur));
    /* ecoute sur la socket */
    listen(sockets.socket_serveur,5);
    sockets.mon_address_longueur = sizeof(sockets.adresse_serveur);
}
/**
 * \fn void connexion_client()
 * \brief Cette fonction bloquante, permet d'attendre qu'un client (autre pc) se connect au serveur(ce pc)
 */
void connexion_client()
{
    /* on attend que le client se connecte */
    sockets.socket_client = accept(sockets.socket_serveur,(struct sockaddr *)&(sockets.socket_client),&(sockets.mon_address_longueur));
}

/**
 * \fn void lire_socket()
 * \brief Cette fonction traite les données présentes sur la socket
 */
void lire_socket()
{
    memset(sockets.buffer,0,sizeof(char)*SIZE_BUFFER);
    recv(sockets.socket_client, sockets.buffer, sizeof(sockets.buffer),0);
    if(sockets.buffer[0]=='$')
    {
        int i=1;
        for(int y=0; y<5; y++)
        {
            struct_jeu.tableau_event[J2][y]=sockets.buffer[i++];
        }
        for(int y=0; y<5; y++)
        {
            struct_jeu.tableau_event[J4][y]=sockets.buffer[i++];
        }
    }
}

/**
 * \fn void ecrire_socket()
 * \brief Cette fonction permet d'envoyer des données sur la socket
 */
void ecrire_socket() //struct_jeu.tableau_event[J2/J4][0->3]
{
    sockets.buffer[0]='$';
    int i=1;
    for(int y=0; y<4; y++)
    {
        sockets.buffer[i++]=struct_jeu.tableau_event[J2][y];
    }
    for(int y=0; y<4; y++)
    {
        sockets.buffer[i++]=struct_jeu.tableau_event[J4][y];
    }

    send(sockets.socket_serveur,sockets.buffer,sizeof(sockets.buffer),0);
}

/**
 * \fn void destruction_socket()
 * \brief Cette fonction met fin à la socket, elle libère l'espace
 */
void destruction_socket()
{
    shutdown(sockets.socket_serveur,2);
    close(sockets.socket_serveur);
}
