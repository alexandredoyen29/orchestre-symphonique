#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "constantes.h"

typedef struct informationsInstrument
{
	int id;
	char nom[NOMBRE_MAX_DE_CARACTERES_DU_NOM_D_UN_INSTRUMENT];
} t_informationsInstrument;

typedef struct listeInstruments
{
	int nombreDInstruments;
	t_informationsInstrument informationsDesInstruments[NOMBRE_MAX_D_INSTRUMENTS];
} t_listeInstruments;

#endif
