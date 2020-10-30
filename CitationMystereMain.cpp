// CitationMystereMain.cpp
// Fichier principale du programme "Citation Myst�re".
//
// Auteur: Harley Lounsbury
// Date: 2019-09-06

#include "fonctions.h"

int main()
{
	setlocale(LC_ALL, "");

	// D�claration de variables.
	string nomFichierSource;
	string ligneCourante;
	int noCitation = 0;

	srand(time(NULL));

	// Demander a l'utilisateur le nom du fichier source.
	saisirNomFichierSource(nomFichierSource);

	// Flux de fichier d'entr�e.
	ifstream fichierCitations(nomFichierSource);

	// Tant que le flux n'est pas arriv� � la fin du fichier.
	while (fichierCitations.good())
	{
		getline(fichierCitations, ligneCourante);
		noCitation++;

		system("cls");
	
		traitementCitation(ligneCourante, noCitation);
	}

	system("cls");
	cout << "Traitement de citations termin�." << endl;
	system("pause");
	
	return 0;
}