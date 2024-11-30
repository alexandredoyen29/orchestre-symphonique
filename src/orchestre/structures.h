#ifndef STRUCTURES_ORCHESTRE_H
#define STRUCTURES_ORCHESTRE_H

// OpenAL
#include <AL/al.h>

#include "../commun/structures.h"

typedef struct informationsPourLeTraitementDUnClient
{
	int fdSocketDuClient;
	ALuint* sources;
	t_listeInstruments* listeDesInstruments;
} t_informationsPourLeTraitementDUnClient;

#endif
