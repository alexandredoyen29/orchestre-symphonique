#include <stdio.h>
#include <stdlib.h>

#include "../commun/socket.h"
#include "../commun/constantes.h"

#include "fonctions.h"

int main(int argc, char** argv)
{
	int retour, socketVersLOrchestre, idInstrumentChoisi;
	t_action choixUtilisateur;
	char* adresseDuServeur;

	if (argc == 2)
	{
		adresseDuServeur = argv[1];

		socketVersLOrchestre = creerFDSocketEnModeClient(adresseDuServeur, PORT_D_ECOUTE);

		if (socketVersLOrchestre > -1)
		{
			// On demande quel instrument on contrôle
			afficherLaListeDesInstruments(socketVersLOrchestre);

			printf("Choisissez un instrument dans la liste");
			scanf("%d", &idInstrumentChoisi);

			do
			{
				choixUtilisateur = recupererLeChoixUtilisateur();

				switch (choixUtilisateur)
				{
					case LANCER_L_INSTRUMENT:
						lancerLInstrument(socketVersLOrchestre, idInstrumentChoisi);
						break;

					case METTRE_EN_PAUSE_L_INSTRUMENT:
						mettreEnPauseLInstrument(socketVersLOrchestre, idInstrumentChoisi);
						break;

					case ARRETER_L_INSTRUMENT:
						arreterLInstrument(socketVersLOrchestre, idInstrumentChoisi);
						break;

					case AVOIR_LA_LISTE_DES_INSTRUMENTS:
						afficherLaListeDesInstruments(socketVersLOrchestre);
						break;

					case CHANGER_LE_VOLUME_DE_L_INSTRUMENT:
						afficherLeChangementDeVolumeDeLInstrument(socketVersLOrchestre, idInstrumentChoisi);
						break;

					case AVOIR_LE_VOLUME_DE_L_INSTRUMENT:
						afficherLeChangementDeVolumeDeLInstrument(socketVersLOrchestre, idInstrumentChoisi);
						break;

					case AVOIR_LA_POSITION_DE_L_INSTRUMENT:
						afficherLeChangementDePostionDeLInstrument(socketVersLOrchestre, idInstrumentChoisi);
						break;

					case AVOIR_LA_DIRECTION_DE_L_INSTRUMENT:
						afficherLeChangementDeDirectionDeLInstrument(socketVersLOrchestre, idInstrumentChoisi);
						break;

					case CHANGER_LA_POSITION_DE_L_INSTRUMENT:
						afficherLeChangementDePostionDeLInstrument(socketVersLOrchestre, idInstrumentChoisi);
						break;

					case CHANGER_LA_DIRECTION_DE_L_INSTRUMENT:
						afficherLeChangementDeDirectionDeLInstrument(socketVersLOrchestre, idInstrumentChoisi);
						break;

					case SUPPRIMER_L_INSTRUMENT:
						supprimerLInstrument(socketVersLOrchestre, idInstrumentChoisi);
						break;

					case ACTION_INCONNUE:
						break;
				}
			}
			while (choixUtilisateur != SUPPRIMER_L_INSTRUMENT);

			retour = EXIT_SUCCESS;
		}
		else
		{
			fprintf(stderr, "Erreur lors de la connexion\n");

			retour = EXIT_FAILURE;
		}
	}
	else
	{
		fprintf(stderr, "Usage : %s <Adresse du serveur>", argv[0]);

		retour = EXIT_FAILURE;
	}

	return retour;
}
