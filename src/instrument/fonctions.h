#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#include "../commun/protocole.h"
#include "../commun/socket.h"
#include "../commun/structures.h"

void afficherLeMenuDesActionsUtilisateur();
t_action recupererLeChoixUtilisateur();
void envoyerUnOrdreALorchestre(int fdSocketVersLOrchestre, t_instrumentCommande* ordre);
void avoirLaListeDesInstruments(int fdSocketVersLOrchestre, t_listeInstruments* destination);
void afficherLaListeDesInstruments(int fdSocketVersLOrchestre);
void lancerLInstrument(int fdSocketVersLOrchestre, int idInstrumentChoisi);
void mettreEnPauseLInstrument(int fdSocketVersLOrchestre, int idInstrumentChoisi);
void arreterLInstrument(int fdSocketVersLOrchestre, int idInstrumentChoisi);
void changerLaPositionDeLInstrument(int fdSocketVersLOrchestre, int idInstrument, float nx, float ny, float nz);
void changerLeVolumeDeLInstrument(int socketVersLOrchestre, int idInstrumentChoisi, float nouveauVolume);
void afficherLeChangementDeVolumeDeLInstrument(int socketVersLOrchestre, int idInstrumentChoisi);
void afficherLeChangementDePostionDeLInstrument(int socketVersLOrchestre, int idInstrumentChoisi);
void changerLaDirectionDeLInstrument(int fdSocketVersLOrchestre, int idInstrument, float nx, float ny, float nz);
void afficherLeChangementDeDirectionDeLInstrument(int socketVersLOrchestre, int idInstrumentChoisi);
void supprimerLInstrument(int socketVersLOrchestre, int idInstrumentChoisi);

#endif
