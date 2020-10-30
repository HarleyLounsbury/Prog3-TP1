// CitationMystereMain.cpp
// Fichier principale du programme "Citation Mystère".
//
// Auteur: Harley Lounsbury
// Date: 2019-09-06

#include "fonctions.h"

int main()
{
	setlocale(LC_ALL, "");

	// Déclaration de variables.
	string nomFichierSource;
	string ligneCourante;
	int noCitation = 0;

	srand(time(NULL));

	// Demander a l'utilisateur le nom du fichier source.
	saisirNomFichierSource(nomFichierSource);

	// Flux de fichier d'entrée.
	ifstream fichierCitations(nomFichierSource);

	// Tant que le flux n'est pas arrivé à la fin du fichier.
	while (fichierCitations.good())
	{
		getline(fichierCitations, ligneCourante);
		noCitation++;

		system("cls");
	
		traitementCitation(ligneCourante, noCitation);
	}

	system("cls");
	cout << "Traitement de citations terminé." << endl;
	system("pause");
	
	return 0;
}