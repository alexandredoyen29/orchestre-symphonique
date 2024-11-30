#include "fonctions.h"

void afficherLeMenuDesActionsUtilisateur()
{
	printf("Bienvenue dans le contrôle de l'instrument !\n");
	printf("Veuillez faire votre choix :\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("\t1) Lancer l'instrument\n");
	printf("\t2) Mettre en pause l'instrument\n");
	printf("\t3) Arrêter l'instrument\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("\t4) Changer le volume de l'instrument\n");
	printf("\t5) Changer la position de l'instrument\n");
	printf("\t6) Changer la direction de l'instrument\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("\t7) Supprimer l'instrument\n");
}

t_action recupererLeChoixUtilisateur()
{
	int entreeUtilisateur;
	t_action choixUtilisateur;

	afficherLeMenuDesActionsUtilisateur();

	scanf("%d", &entreeUtilisateur);

	switch (entreeUtilisateur)
	{
		case 1:
			choixUtilisateur = LANCER_L_INSTRUMENT;
			break;

		case 2:
			choixUtilisateur = METTRE_EN_PAUSE_L_INSTRUMENT;
			break;

		case 3:
			choixUtilisateur = ARRETER_L_INSTRUMENT;
			break;

		case 4:
			choixUtilisateur = CHANGER_LE_VOLUME_DE_L_INSTRUMENT;
			break;

		case 5:
			choixUtilisateur = CHANGER_LA_POSITION_DE_L_INSTRUMENT;
			break;

		case 6:
			choixUtilisateur = CHANGER_LA_DIRECTION_DE_L_INSTRUMENT;
			break;

		case 7:
			choixUtilisateur = SUPPRIMER_L_INSTRUMENT;
			break;

		default:
			choixUtilisateur = ACTION_INCONNUE;
			break;
	}

	return choixUtilisateur;
}

void envoyerUnOrdreALorchestre(int fdSocketVersLOrchestre, t_instrumentCommande* ordre)
{
	envoyerDonneesSurUnSocket(fdSocketVersLOrchestre, ordre, sizeof(t_instrumentCommande));
}

void avoirLaListeDesInstruments(int fdSocketVersLOrchestre, t_listeInstruments* destination)
{
	t_instrumentCommande commande;

	commande.actionDemandee = AVOIR_LA_LISTE_DES_INSTRUMENTS;

	envoyerUnOrdreALorchestre(fdSocketVersLOrchestre, &commande);
	recevoirDonneesDUnSocket(fdSocketVersLOrchestre, destination, sizeof(t_listeInstruments));
}

void afficherLaListeDesInstruments(int fdSocketVersLOrchestre)
{
	t_listeInstruments instruments;
	int i;

	avoirLaListeDesInstruments(fdSocketVersLOrchestre, &instruments);

	printf("Liste des instruments :\n");
	printf("-----------------------------------------------------------------------\n");

	for (i = 0; i < instruments.nombreDInstruments; ++i)
	{
		printf("Id : %d, Nom : %s\n", instruments.informationsDesInstruments[i].id, instruments.informationsDesInstruments[i].nom);
	}

	printf("-----------------------------------------------------------------------\n\n");
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

void afficherLeChangementDeVolumeDeLInstrument(int fdSocketVersLOrchestre, int idInstrumentChoisi)
{
	t_instrumentCommande commande;
	float volumeActuel, nouveauVolume;
	int volumeActuelEnPourcentage, nouveauVolumeEnPourcentage;

	commande.actionDemandee = AVOIR_LE_VOLUME_DE_L_INSTRUMENT;
	commande.idInstrument = idInstrumentChoisi;

	envoyerUnOrdreALorchestre(fdSocketVersLOrchestre, &commande);
	recevoirDonneesDUnSocket(fdSocketVersLOrchestre, &volumeActuel, 3 * sizeof(float));

	volumeActuelEnPourcentage = (int)(volumeActuel * 100);	// Par défaut, le volume vaut 1.00, et il est inutile de dépasser ce seuil

	printf("Volume actuel de l'instrument : %d%%\n", volumeActuelEnPourcentage);
	printf("Entrez le nouveau volume (0 - 100%%) :\n");
	scanf("%d", &nouveauVolumeEnPourcentage);

	nouveauVolume = (float)(nouveauVolumeEnPourcentage / 100.0);

	changerLeVolumeDeLInstrument(fdSocketVersLOrchestre, idInstrumentChoisi, nouveauVolume);
}

void afficherLeChangementDePostionDeLInstrument(int fdSocketVersLOrchestre, int idInstrumentChoisi)
{
	t_instrumentCommande commande;
	float positionActuelle[3], nouvellePosition[3];

	commande.actionDemandee = AVOIR_LA_POSITION_DE_L_INSTRUMENT;
	commande.idInstrument = idInstrumentChoisi;

	envoyerUnOrdreALorchestre(fdSocketVersLOrchestre, &commande);
	recevoirDonneesDUnSocket(fdSocketVersLOrchestre, &positionActuelle, 3 * sizeof(float));

	printf("Position actuelle du nouvel instrument : x = %f, y = %f, z = %f\n", positionActuelle[0], positionActuelle[1], positionActuelle[2]);
	printf("Entrez la nouvelle position x :\n");
	scanf("%f", &nouvellePosition[0]);
	printf("Entrez la nouvelle position y :\n");
	scanf("%f", &nouvellePosition[1]);
	printf("Entrez la nouvelle position z :\n");
	scanf("%f", &nouvellePosition[2]);

	changerLaPositionDeLInstrument(fdSocketVersLOrchestre, idInstrumentChoisi, nouvellePosition[0], nouvellePosition[1], nouvellePosition[2]);
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

void afficherLeChangementDeDirectionDeLInstrument(int fdSocketVersLOrchestre, int idInstrumentChoisi)
{
	t_instrumentCommande commande;
	float directionActuelle[3], nouvelleDirection[3];

	commande.actionDemandee = AVOIR_LA_DIRECTION_DE_L_INSTRUMENT;
	commande.idInstrument = idInstrumentChoisi;

	envoyerUnOrdreALorchestre(fdSocketVersLOrchestre, &commande);
	recevoirDonneesDUnSocket(fdSocketVersLOrchestre, &directionActuelle, 3 * sizeof(float));

	printf("Direction actuelle du nouvel instrument : x = %f, y = %f, z = %f\n", directionActuelle[0], directionActuelle[1], directionActuelle[2]);
	printf("Entrez la nouvelle direction x :\n");
	scanf("%f", &nouvelleDirection[0]);
	printf("Entrez la nouvelle direction y :\n");
	scanf("%f", &nouvelleDirection[1]);
	printf("Entrez la nouvelle direction z :\n");
	scanf("%f", &nouvelleDirection[2]);

	changerLaDirectionDeLInstrument(fdSocketVersLOrchestre, idInstrumentChoisi, nouvelleDirection[0], nouvelleDirection[1], nouvelleDirection[2]);
}

void supprimerLInstrument(int socketVersLOrchestre, int idInstrumentChoisi)
{
	t_instrumentCommande commande;

	commande.actionDemandee = SUPPRIMER_L_INSTRUMENT;
	commande.idInstrument = idInstrumentChoisi;

	envoyerUnOrdreALorchestre(socketVersLOrchestre, &commande);
}
