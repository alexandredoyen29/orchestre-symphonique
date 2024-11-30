#include "socket.h"

int creerFDSocketEnModeServeur(int port)
{
	int fdSocket, valeurOptionReutilisation = 1, resultatLiaisonInterfaceSocket, resultat;
	struct sockaddr_in interface = { 0 };

	fdSocket = socket(AF_INET, SOCK_STREAM, 0);	// Socket TCP

	if (fdSocket > -1)	// Si le descripteur du socket est -1, cela signifie qu'il n'a pas pu se créer :(
	{
		interface.sin_addr.s_addr = htonl(INADDR_ANY);	// Accepte toutes les connexions
		interface.sin_family = AF_INET;	// Interface IPv4
		interface.sin_port = htons((__uint16_t)port);

		setsockopt(fdSocket, SOL_SOCKET, SO_REUSEADDR, &valeurOptionReutilisation, sizeof(int));	// On permet la réutilisation de l'adresse alors que le programme vient d'être tué. Cela permet de relancer imédiatement le serveur après un éventuel arrêt

		resultatLiaisonInterfaceSocket = bind(fdSocket, (struct sockaddr*)&interface, sizeof(struct sockaddr_in));	// On lie l'interface au socket précédemment créé

		if (resultatLiaisonInterfaceSocket > -1)	// Pareil, si la valeur retournée est -1, il y a une erreur et errno est positionnée
		{
			resultat = fdSocket;
		}
		else
		{
			perror("Erreur sur la fonction bind()");
			resultat = -1;
		}
	}
	else
	{
		perror("Erreur sur la fonction socket()");
		resultat = -1;
	}

	return resultat;
}

int creerFDSocketEnModeClient(char* adresse, int port)
{
	int fdSocket, resultat, resultatUtilisationAdresseFournie, resultatConnexion;
	struct sockaddr_in interface = { 0 };

	fdSocket = socket(AF_INET, SOCK_STREAM, 0);	// Socket TCP

	if (fdSocket > -1)	// Si le descripteur du socket est -1, cela signifie qu'il n'a pas pu se créer :(
	{
		resultatUtilisationAdresseFournie = inet_pton(AF_INET, adresse, &interface.sin_addr);

		if (resultatUtilisationAdresseFournie > -1)
		{
			interface.sin_family = AF_INET;	// Interface IPv4
			interface.sin_port = htons((__uint16_t)port);

			resultatConnexion = connect(fdSocket, (struct sockaddr*)&interface, sizeof(struct sockaddr));

			if (resultatConnexion > -1)	// Si la valeur retournée est -1, il y a une erreur
			{
				resultat = fdSocket;
			}
			else
			{
				perror("Erreur sur la fonction connect()");
				resultat = -1;
			}
		}
		else
		{
			fprintf(stderr, "Erreur d'adresse fournie");
			resultat = -1;
		}
	}
	else
	{
		perror("Erreur sur la fonction socket()");
		resultat = -1;
	}

	return resultat;
}

int ecouterSocket(int fdSocket, struct sockaddr_in* interfaceSocketNouvelleConnexion)
{
	int resultat, fdSocketNouvelleConnexion;
	unsigned int tailleInterface;

	resultat = listen(fdSocket, NB_CONNEXION_ENTRANTES_MAX);	// On écoute le socket de descripteur `fdSocket` avec `NB_CONNEXION_ENTRANTES_MAX` (Constante définie dans "socket.h") connexions entrantes maximum

	if (resultat > -1)
	{
		tailleInterface = sizeof(struct sockaddr_in);

		fdSocketNouvelleConnexion = accept(fdSocket, (struct sockaddr*)interfaceSocketNouvelleConnexion, &tailleInterface);	// On accepte la nouvelle connexion entrante, et on récupère un socket permettant de renvoyer un résultat. Cet appel système attend la nouvelle connexion

		if (fdSocketNouvelleConnexion > -1)
		{
			resultat = fdSocketNouvelleConnexion;
		}
		else
		{
			if (errno == EINTR)	// Cas de l'appel système "accept()" interrompu par un signal (Cas le plus probable : SIGCHLD)
			{
				resultat = -2;
			}
			else
			{
				perror("Erreur sur la fonction accept():");
				resultat = -1;
			}
		}
	}
	else
	{
		perror("Erreur sur la fonction listen()");
	}

	return resultat;
}

ssize_t envoyerDonneesSurUnSocket(int fdSocket, void* tampon, size_t tailleDuTampon)
{
	ssize_t resultat = send(fdSocket, tampon, tailleDuTampon, 0);	// Le 0 en dernier paramètre iundique l'absence de drapeaux (Voir send(2))

	if (resultat < 0)
	{
		perror("Erreur sur la fonction send()");
	}

	return resultat;
}

ssize_t recevoirDonneesDUnSocket(int fdSocket, void* tampon, size_t tailleDuTampon)
{
	ssize_t resultat = recv(fdSocket, tampon, tailleDuTampon, 0);	// Le 0 en dernier paramètre iundique l'absence de drapeaux (Voir recv(2))

	if (resultat < 0)
	{
		perror("Erreur sur la fonction recv()");
	}

	return resultat;
}

int fermerSocket(int fdSocket)
{
	int resultat = close(fdSocket);

	if (resultat == -1)
	{
		perror("Erreur sur la fonction close()");
	}

	return resultat;
}
