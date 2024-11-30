#include "fichier.h"

int creerFDFichierEnLecture(const char* chemin)
{
	int resultat = open(chemin, O_RDONLY);

	if (resultat < 0)
	{
		perror("Erreur sur la fonction open()");
	}

	return resultat;
}

ssize_t lireUnFichier(const int fdFichier, void* tampon, const size_t nombreDOctetesALire)
{
	ssize_t resultat = read(fdFichier, tampon, nombreDOctetesALire);

	if (resultat < 0)
	{
		perror("Erreur sur la fonction read()");
	}

	return resultat;
}

int fermerFichier(const int fdFichier)
{
	int resultat = close(fdFichier);

	if (resultat == -1)
	{
		perror("Erreur sur la fonction close()");
	}

	return resultat;
}
