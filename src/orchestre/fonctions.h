#ifndef FONCTIONS_H
#define FONCTIONS_H

// OpenAL
#include <AL/al.h>

#include <string.h>

#include "../commun/socket.h"
#include "../commun/protocole.h"
#include "../commun/semaphore.h"
#include "../commun/structures.h"

#include "structures.h"

void detruireLOrchestre(int nombreDeSources, ALuint* sources);
void envoyerLaListeDesInstruments(int fdSocketVersLeClient, t_listeInstruments* listeDesInstruments);
void lancerLInstrument(ALuint source);
void mettreEnPauseLInstrument(ALuint source);
void arreterLInstrument(ALuint source);
void envoyerLeVolumeDeLInstrument(int fdSocketVersLeClient, ALuint source);
void changerLeVolumeDeLInstrument(ALuint source, float nouveauVolume);
void envoyerLaPositionDeLInstrument(int fdSocketVersLeClient, ALuint source);
void changerLaPositionDeLInstrument(ALuint source, float* nouvellePosition);
void envoyerLaDirectionDeLInstrument(int fdSocketVersLeClient, ALuint source);
void changerLaDirectionDeLInstrument(ALuint source, float* nouvelleDirection);
void* traitementDeLaDemandeDuClient(void* argument);

#endif
