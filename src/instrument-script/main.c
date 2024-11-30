#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../commun/socket.h"
#include "../commun/constantes.h"
#include "../commun/fichier.h"

#include "fonctions.h"

int main(int argc, char** argv)
{
	int retour, socketVersLOrchestre, idInstrumentChoisi, fdFichierContenantLeScript, valeurEntiereDuParametreDeLInstructionCourante, i;
	char* adresseDuServeur;
	char* nomDuScript;
	char* idInstrumentChoisiSousFormeDeChaine;
	char* contenuDuScriptApresLaLigneSelectionnantLInstrument;
	char* contexteStrtokLorsDuParcoursDesLignesDuScript = NULL;
	char* instructionCouranteDuScript;
	char* parametreDeLInstructionCouranteDuScript;
	char contenuDuScript[TAILLE_MAXIMALE_DU_FICHIER_SCRIPT];
	float valeursFlottantesDuParametreDeLInstructionCourante[3];

	if (argc == 3)
	{
		adresseDuServeur = argv[1];
		nomDuScript = argv[2];

		socketVersLOrchestre = creerFDSocketEnModeClient(adresseDuServeur, PORT_D_ECOUTE);

		if (socketVersLOrchestre > -1)
		{
			// Lecture du fichier contenant la partition (script)
			fdFichierContenantLeScript = creerFDFichierEnLecture(nomDuScript);
			lireUnFichier(fdFichierContenantLeScript, contenuDuScript, TAILLE_MAXIMALE_DU_FICHIER_SCRIPT * sizeof(char));
			fermerFichier(fdFichierContenantLeScript);

			// On part du postulat que la première ligne du fichier contient "INSTRUMENT <Numéro>"
			strtok(contenuDuScript, " ");
			idInstrumentChoisiSousFormeDeChaine = strtok(NULL, "\n");

			idInstrumentChoisi = atoi(idInstrumentChoisiSousFormeDeChaine);

			contenuDuScriptApresLaLigneSelectionnantLInstrument = idInstrumentChoisiSousFormeDeChaine + strlen(idInstrumentChoisiSousFormeDeChaine) + 1;	// Vu que strtok change le "\n" de la dernière ligne par un "\0", pour récupérer le reste, on prend le pointeur vers la chaîne modifiée par strtok + la taille de cette chaîne + 1 pour dépasser le "\0" qui était initialement un "\n".

			contenuDuScriptApresLaLigneSelectionnantLInstrument = strtok_r(contenuDuScriptApresLaLigneSelectionnantLInstrument, "\n", &contexteStrtokLorsDuParcoursDesLignesDuScript);

			do
			{
				// Récupération de l'ordre de la ligne courante de la partition (script)
				instructionCouranteDuScript = strtok(contenuDuScriptApresLaLigneSelectionnantLInstrument, " ");
				parametreDeLInstructionCouranteDuScript = strtok(NULL, "\n");

				if (strcmp(instructionCouranteDuScript, "LECTURE") == 0)
				{
					lancerLInstrument(socketVersLOrchestre, idInstrumentChoisi);
				}
				else if (strcmp(instructionCouranteDuScript, "PAUSE") == 0)
				{
					mettreEnPauseLInstrument(socketVersLOrchestre, idInstrumentChoisi);
				}
				else if (strcmp(instructionCouranteDuScript, "STOP") == 0)
				{
					arreterLInstrument(socketVersLOrchestre, idInstrumentChoisi);
				}
				else if (strcmp(instructionCouranteDuScript, "VOLUME") == 0)
				{
					valeursFlottantesDuParametreDeLInstructionCourante[0] = strtof(parametreDeLInstructionCouranteDuScript, NULL);

					changerLeVolumeDeLInstrument(socketVersLOrchestre, idInstrumentChoisi, valeursFlottantesDuParametreDeLInstructionCourante[0]);
				}
				else if (strcmp(instructionCouranteDuScript, "POSITION") == 0)
				{
					parametreDeLInstructionCouranteDuScript = strtok(parametreDeLInstructionCouranteDuScript, " ");

					for (i = 0; i < 3; ++i)	// 3 Car on travaille sur un vecteur flotant de dimension 3
					{
						valeursFlottantesDuParametreDeLInstructionCourante[i] = strtof(parametreDeLInstructionCouranteDuScript, NULL);

						parametreDeLInstructionCouranteDuScript = strtok(NULL, " ");
					}

					changerLaPositionDeLInstrument(socketVersLOrchestre, idInstrumentChoisi, valeursFlottantesDuParametreDeLInstructionCourante[0], valeursFlottantesDuParametreDeLInstructionCourante[1], valeursFlottantesDuParametreDeLInstructionCourante[2]);
				}
				else if (strcmp(instructionCouranteDuScript, "DIRECTION") == 0)
				{
					parametreDeLInstructionCouranteDuScript = strtok(parametreDeLInstructionCouranteDuScript, " ");

					for (i = 0; i < 3; ++i)	// 3 Car on travaille sur un vecteur flotant de dimension 3
					{
						valeursFlottantesDuParametreDeLInstructionCourante[i] = strtof(parametreDeLInstructionCouranteDuScript, NULL);

						parametreDeLInstructionCouranteDuScript = strtok(NULL, " ");
					}

					changerLaDirectionDeLInstrument(socketVersLOrchestre, idInstrumentChoisi, valeursFlottantesDuParametreDeLInstructionCourante[0], valeursFlottantesDuParametreDeLInstructionCourante[1], valeursFlottantesDuParametreDeLInstructionCourante[2]);
				}
				else if (strcmp(instructionCouranteDuScript, "QUITTER") == 0)
				{
					supprimerLInstrument(socketVersLOrchestre, idInstrumentChoisi);
				}
				else if (strcmp(instructionCouranteDuScript, "ATTENTE") == 0)
				{
					valeurEntiereDuParametreDeLInstructionCourante = atoi(parametreDeLInstructionCouranteDuScript);

					sleep((unsigned int)valeurEntiereDuParametreDeLInstructionCourante);
				}
				else
				{
					fprintf(stderr, "Erreur : Commande \"%s\" inconnue\n", instructionCouranteDuScript);
				}

				contenuDuScriptApresLaLigneSelectionnantLInstrument = strtok_r(NULL, "\n", &contexteStrtokLorsDuParcoursDesLignesDuScript);
			}
			while (contenuDuScriptApresLaLigneSelectionnantLInstrument != NULL);

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
		fprintf(stderr, "Usage : %s <Adresse du serveur> <Nom du script>", argv[0]);

		retour = EXIT_FAILURE;
	}

	return retour;
}
