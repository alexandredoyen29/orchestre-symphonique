// Bibliothèque standard du C

#include <stdlib.h>

// OpenAL
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

// Threads
#include <pthread.h>

#include "../commun/socket.h"
#include "../commun/constantes.h"
#include "../commun/semaphore.h"
#include "../commun/structures.h"

#include "fonctions.h"

int main(int argc, char** argv)
{
	int retour, i, fdSocketEcoute, fdSocketCommunicationAvecLeControleDistant, initSemaphore = 0;
	ALuint tampon;
	ALuint* sources;
	ALCdevice* peripherique;
	ALCcontext* contexte;
	struct sockaddr_in interfaceSocketCommunicationAvecLeControleDistant;
	pthread_t thread;
	t_listeInstruments listeInstruments;
	t_informationsPourLeTraitementDUnClient informationsEnvoyeesAuNouveauThread;

	if (argc < 2)	// On contrôle la présence du nom de fichier en argument
	{
		fprintf(stderr, "Il manque un argument. Le programme se lance ainsi : '%s <nomDuFichier.wav>'\n", argv[0]);

		retour = EXIT_FAILURE;
	}
	else
	{
		// Étape 0 : Initialisation d'OpenAL, et gestion du périphérique et du contexte + Sémaphores

		alutInit(0, NULL);
		peripherique = alcOpenDevice(NULL);	// Le paramètre NULL indique que l'on prend le périphérique par défaut
		contexte = alcCreateContext(peripherique, NULL);	// Le paramètre NULL indique que l'on initialise pas le contexte avec des attributs
		alcMakeContextCurrent(contexte);
		initSem(1, argv[0], &initSemaphore);

		// Étape 1 : Récupération des sources passées en argument du programme

		listeInstruments.nombreDInstruments = argc - 1;	// - 1 car on ne prend pas l'argument d'indice 0 qui est le nom du programme lui-même
		sources = malloc((size_t)((long unsigned int)(listeInstruments.nombreDInstruments) * sizeof(int)));

		for (i = 1; i < argc; ++i)
		{
			// Gestion de la liste des instruments
			listeInstruments.informationsDesInstruments[i - 1].id = i - 1;
			strcpy(listeInstruments.informationsDesInstruments[i - 1].nom, argv[i]);

			// Gestion du tampon et des sources audio
			tampon = alutCreateBufferFromFile(argv[i]);
			sources[i - 1] = (long int)1;	// Le tableau "source" commence à l'indice 0, contrairement à i qui comment à 1, d'où le "sources[i - 1]"

			alGenSources(1, &sources[i - 1]);
			alSourcei(sources[i - 1], AL_BUFFER, (ALint)tampon);

			// Gestion des angles internes et externes des instruments (Sources audio)
			alSourcef(sources[i - 1], AL_CONE_INNER_ANGLE, ANGLE_INTERNE_D_UN_INSTRUMENT);
			alSourcef(sources[i - 1], AL_CONE_OUTER_ANGLE, ANGLE_EXTERNE_D_UN_INSTRUMENT);
		}

		// Étape 2 : Mise en place de la communication réseau avec le contrôle distant
		
		fdSocketEcoute = creerFDSocketEnModeServeur(PORT_D_ECOUTE);

		if (fdSocketEcoute > -1)
		{
			while (1)
			{
				fdSocketCommunicationAvecLeControleDistant = ecouterSocket(fdSocketEcoute, &interfaceSocketCommunicationAvecLeControleDistant);

				informationsEnvoyeesAuNouveauThread.fdSocketDuClient = fdSocketCommunicationAvecLeControleDistant;
				informationsEnvoyeesAuNouveauThread.sources = sources;
				informationsEnvoyeesAuNouveauThread.listeDesInstruments = &listeInstruments;

				pthread_create(&thread, NULL, traitementDeLaDemandeDuClient, &informationsEnvoyeesAuNouveauThread);
				P(0);	// Blocage du sémaphore gérant la création des threads
			}
		}

		detruireLOrchestre(listeInstruments.nombreDInstruments, sources);

		alDeleteBuffers(1, &tampon);
		alcDestroyContext(contexte);
		alcCloseDevice(peripherique);

		retour = EXIT_SUCCESS;
	}

	return retour;
}
