#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define NB_CONNEXION_ENTRANTES_MAX 5	// Au maximum, cinq connexions entrantes

int creerFDSocketEnModeServeur(int port);
int creerFDSocketEnModeClient(char* adresse, int port);
int ecouterSocket(int fdSocket, struct sockaddr_in* interfaceSocketNouvelleConnexion);
ssize_t envoyerDonneesSurUnSocket(int fdSocket, void* tampon, size_t tailleDuTampon);
ssize_t recevoirDonneesDUnSocket(int fdSocket, void* tampon, size_t tailleDuTampon);
int fermerSocket(int fdSocket);

#endif
