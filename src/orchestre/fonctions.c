#include "fonctions.h"

void detruireLOrchestre(int nombreDeSources, ALuint* sources)
{
	int i;

	for (i = 0; i < nombreDeSources; ++i)
	{
		alDeleteSources(1, &sources[i]);
	}
}

void envoyerLaListeDesInstruments(int fdSocketVersLeClient, t_listeInstruments* listeDesInstruments)
{
	envoyerDonneesSurUnSocket(fdSocketVersLeClient, listeDesInstruments, sizeof(t_listeInstruments));
}

void lancerLInstrument(ALuint source)
{
	alSourcePlay(source);
}

void mettreEnPauseLInstrument(ALuint source)
{
	alSourcePause(source);
}

void arreterLInstrument(ALuint source)
{
	alSourceStop(source);
}

void envoyerLeVolumeDeLInstrument(int fdSocketVersLeClient, ALuint source)
{
	float volume;

	alGetSourcef(source, AL_GAIN, &volume);
	envoyerDonneesSurUnSocket(fdSocketVersLeClient, &volume, sizeof(float));
}

void changerLeVolumeDeLInstrument(ALuint source, float nouveauVolume)
{
	alSourcef(source, AL_GAIN, nouveauVolume);
}

void envoyerLaPositionDeLInstrument(int fdSocketVersLeClient, ALuint source)
{
	float position[3];

	alGetSource3f(source, AL_POSITION, &position[0], &position[1], &position[2]);
	envoyerDonneesSurUnSocket(fdSocketVersLeClient, &position, 3 * sizeof(float));
}

void changerLaPositionDeLInstrument(ALuint source, float* nouvellePosition)
{
	alSource3f(source, AL_POSITION, nouvellePosition[0], nouvellePosition[1], nouvellePosition[2]);
}

void envoyerLaDirectionDeLInstrument(int fdSocketVersLeClient, ALuint source)
{
	float direction[3];

	alGetSource3f(source, AL_DIRECTION, &direction[0], &direction[1], &direction[2]);
	envoyerDonneesSurUnSocket(fdSocketVersLeClient, &direction, 3 * sizeof(float));
}

void changerLaDirectionDeLInstrument(ALuint source, float* nouvelleDirection)
{
	alSource3f(source, AL_DIRECTION, nouvelleDirection[0], nouvelleDirection[1], nouvelleDirection[2]);
}

void* traitementDeLaDemandeDuClient(void* argument)
{
	t_informationsPourLeTraitementDUnClient informationsTransmises;
	t_instrumentCommande commande;

	memcpy(&informationsTransmises, argument, sizeof(struct informationsPourLeTraitementDUnClient));
	V(0);	// Libération du sémaphore bloquant la création des threads

	do
	{
		recevoirDonneesDUnSocket(informationsTransmises.fdSocketDuClient, &commande, sizeof(struct instrumentCommande));

		switch (commande.actionDemandee)
		{
			case LANCER_L_INSTRUMENT:
				lancerLInstrument(informationsTransmises.sources[commande.idInstrument]);
				break;

			case METTRE_EN_PAUSE_L_INSTRUMENT:
				mettreEnPauseLInstrument(informationsTransmises.sources[commande.idInstrument]);
				break;

			case ARRETER_L_INSTRUMENT:
				arreterLInstrument(informationsTransmises.sources[commande.idInstrument]);
				break;

			case AVOIR_LA_LISTE_DES_INSTRUMENTS:
				envoyerLaListeDesInstruments(informationsTransmises.fdSocketDuClient, informationsTransmises.listeDesInstruments);
				break;

			case AVOIR_LE_VOLUME_DE_L_INSTRUMENT:
				envoyerLeVolumeDeLInstrument(informationsTransmises.fdSocketDuClient, informationsTransmises.sources[commande.idInstrument]);
				break;

			case CHANGER_LE_VOLUME_DE_L_INSTRUMENT:
				changerLeVolumeDeLInstrument(informationsTransmises.sources[commande.idInstrument], commande.scalaire);
				break;

			case AVOIR_LA_POSITION_DE_L_INSTRUMENT:
				envoyerLaPositionDeLInstrument(informationsTransmises.fdSocketDuClient, informationsTransmises.sources[commande.idInstrument]);
				break;

			case CHANGER_LA_POSITION_DE_L_INSTRUMENT:
				changerLaPositionDeLInstrument(informationsTransmises.sources[commande.idInstrument], commande.vecteur);
				break;

			case AVOIR_LA_DIRECTION_DE_L_INSTRUMENT:
				envoyerLaDirectionDeLInstrument(informationsTransmises.fdSocketDuClient, informationsTransmises.sources[commande.idInstrument]);
				break;

			case CHANGER_LA_DIRECTION_DE_L_INSTRUMENT:
				changerLaDirectionDeLInstrument(informationsTransmises.sources[commande.idInstrument], commande.vecteur);
				break;

			case SUPPRIMER_L_INSTRUMENT:
				arreterLInstrument(informationsTransmises.sources[commande.idInstrument]);
				break;

			case ACTION_INCONNUE:
				break;
		}
	} while (commande.actionDemandee != SUPPRIMER_L_INSTRUMENT);

	fermerSocket(informationsTransmises.fdSocketDuClient);

	return NULL;
}
