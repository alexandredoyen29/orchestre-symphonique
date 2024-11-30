#include "fonctions.h"

void envoyerUnOrdreALorchestre(int fdSocketVersLOrchestre, t_instrumentCommande* ordre)
{
	envoyerDonneesSurUnSocket(fdSocketVersLOrchestre, ordre, sizeof(t_instrumentCommande));
}

void lancerLInstrument(int fdSocketVersLOrchestre, int idInstrument)
{
	t_instrumentCommande commande;

	commande.actionDemandee = LANCER_L_INSTRUMENT;
	commande.idInstrument = idInstrument;

	envoyerUnOrdreALorchestre(fdSocketVersLOrchestre, &commande);
}

void mettreEnPauseLInstrument(int fdSocketVersLOrchestre, int idInstrument)
{
	t_instrumentCommande commande;

	commande.actionDemandee = METTRE_EN_PAUSE_L_INSTRUMENT;
	commande.idInstrument = idInstrument;

	envoyerUnOrdreALorchestre(fdSocketVersLOrchestre, &commande);
}

void arreterLInstrument(int fdSocketVersLOrchestre, int idInstrument)
{
	t_instrumentCommande commande;

	commande.actionDemandee = ARRETER_L_INSTRUMENT;
	commande.idInstrument = idInstrument;

	envoyerUnOrdreALorchestre(fdSocketVersLOrchestre, &commande);
}

void changerLaPositionDeLInstrument(int fdSocketVersLOrchestre, int idInstrument, float nx, float ny, float nz)
{
	t_instrumentCommande commande;

	commande.actionDemandee = CHANGER_LA_POSITION_DE_L_INSTRUMENT;
	commande.idInstrument = idInstrument;
	commande.vecteur[0] = nx;
	commande.vecteur[1] = ny;
	commande.vecteur[2] = nz;

	envoyerUnOrdreALorchestre(fdSocketVersLOrchestre, &commande);
}

void changerLeVolumeDeLInstrument(int fdSocketVersLOrchestre, int idInstrumentChoisi, float nouveauVolume)
{
	t_instrumentCommande commande;

	commande.actionDemandee = CHANGER_LE_VOLUME_DE_L_INSTRUMENT;
	commande.idInstrument = idInstrumentChoisi;
	commande.scalaire = nouveauVolume;

	envoyerUnOrdreALorchestre(fdSocketVersLOrchestre, &commande);
}

void changerLaDirectionDeLInstrument(int fdSocketVersLOrchestre, int idInstrument, float nx, float ny, float nz)
{
	t_instrumentCommande commande;

	commande.actionDemandee = CHANGER_LA_DIRECTION_DE_L_INSTRUMENT;
	commande.idInstrument = idInstrument;
	commande.vecteur[0] = nx;
	commande.vecteur[1] = ny;
	commande.vecteur[2] = nz;

	envoyerUnOrdreALorchestre(fdSocketVersLOrchestre, &commande);
}

void supprimerLInstrument(int socketVersLOrchestre, int idInstrumentChoisi)
{
	t_instrumentCommande commande;

	commande.actionDemandee = SUPPRIMER_L_INSTRUMENT;
	commande.idInstrument = idInstrumentChoisi;

	envoyerUnOrdreALorchestre(socketVersLOrchestre, &commande);
}
