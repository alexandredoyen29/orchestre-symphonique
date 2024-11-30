#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdlib.h>

#include "../commun/protocole.h"
#include "../commun/socket.h"
#include "../commun/structures.h"

void envoyerUnOrdreALorchestre(int fdSocketVersLOrchestre, t_instrumentCommande* ordre);
void lancerLInstrument(int fdSocketVersLOrchestre, int idInstrumentChoisi);
void mettreEnPauseLInstrument(int fdSocketVersLOrchestre, int idInstrumentChoisi);
void arreterLInstrument(int fdSocketVersLOrchestre, int idInstrumentChoisi);
void changerLaPositionDeLInstrument(int fdSocketVersLOrchestre, int idInstrument, float nx, float ny, float nz);
void changerLeVolumeDeLInstrument(int socketVersLOrchestre, int idInstrumentChoisi, float nouveauVolume);
void changerLaDirectionDeLInstrument(int fdSocketVersLOrchestre, int idInstrument, float nx, float ny, float nz);
void supprimerLInstrument(int socketVersLOrchestre, int idInstrumentChoisi);

#endif
