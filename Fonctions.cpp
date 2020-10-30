// Fonctions.cpp
// Fichier de fonctions pour "Citation Mystère".
//
// Auteur: Harley Lounsbury
// Date: 2019-09-06

#include "Fonctions.h"

void saisirNomFichierSource(string& nomFichierSource)
{
	// Afficher le titre et demander le nom du fichier source.
	cout << "Bienvenue au jeu de Citation Mystère" << endl;
	cout << "Veuillez entrer le nom du fichier source: ";
	getline(cin, nomFichierSource);

	return;
}

void traitementCitation(string ligneCourante, int noCitation)
{
	// Éffectuer des vérifications sur la ligne.
	if (!validerStringASCII(ligneCourante, noCitation))
		return;

	if (!validerLongeurString(ligneCourante, noCitation))
		return;

	// S'occuper des séparateurs adjacent.
	traiterSeparateurs(ligneCourante);

	// Déterminer le longeur optimale de chaque ligne, pour en avoir le moins de mots tronqués.
	int longeurLigne = determinerLongeurLigne(ligneCourante);

	// Convertir tous les caractères en majuscule.
	convertirMajuscule(ligneCourante);

	// Afficher la citation, mélangée.
	afficherHaut(ligneCourante, longeurLigne, noCitation);

	// Afficher les espaces où vont les caractères.
	afficherBas(ligneCourante, longeurLigne, cout);

	// Message pour indiquer que la traitement a terminée.
	cout << "Le fichier 'citation" << noCitation << ".txt' à été créé dans le dossier actuel." << endl;
	system("pause");

	return;
}

void afficherHaut(string ligneCourante, int longeurLigne, int noCitation)
{
	// Créer une copie de la phrase originale, pour conserver le placement des caractères (car on va monter les lettres afficher en haut de la grille)
	string copieOriginal = ligneCourante;

	// Ajouter des espaces pour simuler un tableau. (peut-être pas nécessaire, à vérifier).
	ajouterEspaces(ligneCourante, longeurLigne);

	// Mélanger les lettres en colonne.
	melangerString(ligneCourante, longeurLigne);

	// Afficher la phrase melangée.
	afficherPhrase(ligneCourante, longeurLigne, cout);

	// Écrire la même phrase melangée dans le fichier.
	// Important d'écrire dans le fichier ici: les colonnes mélangées doit être pareilles que qu'est-ce qu'il est affiché à l'écran.
	ecrireDansFichier(ligneCourante, longeurLigne, noCitation, copieOriginal);
		
	cout << setw(longeurLigne * 3 - 2) << setfill('-') << "-" << setfill(' ') << endl;

	return;
}

int determinerLongeurLigne(string ligneCourante)
{
	// Ancre pour mémoriser le longeur avec le moins de mots tronqués.
	int ancre = 0;
	// On commence le longeur par le minimum.
	int longeurLigne = MIN_LIGNE;
	// Boucle pour parcourir les possibilités de longeur de ligne.
	for (int i = MIN_LIGNE; i <= MAX_LIGNE; i++)
	{
		// Pour chaque longeur de ligne, on doit mémoriser le nombre de mots qui sont tronqués.
		int compteurMotsTronques = 0;
		// On doit vérifier que si le premier caractère d'une ligne est alphanumérique et le dernier de la ligne précedente, 
		// on considère que le mot est tronqué. On augmente le compteur.
		for (int j = MIN_LIGNE; j < ligneCourante.length(); j += i)
		{
			if (isalpha(ligneCourante[j]) && isalpha(ligneCourante[j - 1]))
				compteurMotsTronques++;
		}
		// Si on est dans la première itération, c'est le longeur optimale.
		if (i == MIN_LIGNE)
			ancre = compteurMotsTronques;
		// Si on voit qu'une longeur fait moins de mots tronqués, on remplace l'ancre et le longeur optimale.
		if (compteurMotsTronques < ancre)
		{
			ancre = compteurMotsTronques;
			longeurLigne = i;
		}
	}
	return longeurLigne;
}

int aleatoire(const int iMIN, const int iMAX)
{
	// Générer le nombre au hasard, compris entre les limites fournies. 
	return rand() % (iMAX - iMIN + 1) + iMIN;
}

void permuterAleatoire(string& temp)
{
	// Variables locales.
	char tempChar;
	int position1;
	int position2;

	// Boucle pour permuter deux caractères choisis aléatoirement.
	// On éffectue les permutations 10 fois. Arbitraire, mais suffisant pour nos besoins.
	for (int i = 0; i < 10; i++)
	{
		position1 = aleatoire(0, temp.length() - 1);
		position2 = aleatoire(0, temp.length() - 1);
		
		tempChar = temp[position1];
		temp[position1] = temp[position2];
		temp[position2] = tempChar;
	}
	
	// Permuter les espaces à la fin de chaque chaîne qui fait une colonne.
	permuterEspaces(temp);

	return;
}

void convertirMajuscule(string& phrase)
{
	// Des fois, le nom d'une fonction explique toute. 
	for (int i = 0; i < phrase.length(); i++) 
	{
		phrase[i] = toupper(phrase[i]);
	}
	return;
}

void melangerString(string& ligneCourante, int longeurLigne)
{
	string temp;
	// Mélanger les lettres, une colonne à la fois.
	for (int i = 0; i < longeurLigne; i++)
	{
		temp = "";
		// Chercher les lettres d'une colonne.
		for (int j = i; j < ligneCourante.length(); j += longeurLigne)
		{
			temp += ligneCourante[j];
		}
		// Mélanger le string temporaire.
		permuterAleatoire(temp);

		// Remettre les caractères du string temporaire aux bons endroits.
		for (int j = i, k = 0; j < ligneCourante.length(); j += longeurLigne, k++)
		{
			ligneCourante[j] = temp[k];
		}
	}
	return;
}

void afficherBas(string ligneCourante, int longeurLigne, ostream& of)
{
	// Ajouter des espaces pour faire une grille pleine. (peut-être pas nécessaire. À vérifier)
	ajouterEspaces(ligneCourante, longeurLigne);

	// Boucle d'affichage. 
	for (int i = 0; i < ligneCourante.length(); i++)
	{
		// Passe à la ligne, selon le longeur optimale.
		if (i != 0 && i % longeurLigne == 0)
			of << endl;

		// Pour chaque caractère alphanumérique, imprimer _ à sa place, autrement, une espace.
		if (isalpha(ligneCourante[i]))
			of << "_";
		else
			of << " ";
		of << "  ";
	}
	of << endl;
	
	return;
}

void ajouterEspaces(string& ligneCourante, int longeurLigne)
{
	// Ajouter des espaces à la fin pour faire une grille pleine.
	if (ligneCourante.length() % longeurLigne != 0)
	{
		int espaces = ligneCourante.length() % longeurLigne;
		for (int i = 0; i < espaces; i++)
			ligneCourante += " ";
	}

	return;
}

void afficherPhrase(string ligneCourante, int longeurLigne, ostream& of)
{
	// Afficher la phrase caractère par caractère avec deux espaces entre chaque.
	for (int i = 0; i < ligneCourante.length(); i++)
	{
		if (i != 0 && i % longeurLigne == 0)
			of << endl; 
		of << ligneCourante[i] << "  ";
	}
	of << endl;

	return;
}

void permuterEspaces(string& temp)
{
	char tempChar;

	// Trier le string temporaire pour mettre les espaces à la fin (les caractères seront en haut des colonnes).
	for (int i = 0; i < temp.length() - 1; i++)
	{
		for (int j = i + 1; j < temp.length(); j++)
		{
			if (temp[i] == ' ')
			{
				tempChar = temp[i];
				temp[i] = temp[j];
				temp[j] = tempChar;
			}
		}
	}

	return;
}

void ecrireDansFichier(string ligneCourante, int longeurLigne, int noCitation, string copieOriginale)
{
	// Faire le même travail que l'affichage à l'écran, mais dans le fichier. 
	string nomFichierOut = "citation" + to_string(noCitation) + ".txt";
	ofstream fichierOut(nomFichierOut, ios::app);
	afficherPhrase(ligneCourante, longeurLigne, fichierOut);
	afficherBas(copieOriginale, longeurLigne, fichierOut);
	
	fichierOut.close();

	return;
}

bool validerLongeurString(string ligneCourante, int noCitation)
{
	// Vérifier le longeur de la phrase contre le minimum et maximum nombre de caractères.
	// Afficher le message d'erreur approprié.
	if (ligneCourante.length() < MIN_CHAR_CITATION)
	{
		cout << "La citation #" << noCitation << " ne peut pas être traitée car elle est trôp courte." << endl;
		system("pause"); 
		return false;
	}
	if (ligneCourante.length() > MAX_CHAR_CITATION)
	{
		cout << "La citation #" << noCitation << " ne peut pas être traitée car elle est trôp longue." << endl;
		system("pause");
		return false;
	}

	return true;
}

bool validerStringASCII(string ligneCourante, int noCitation)
{
	// Vérifier qu'il n'y a pas de caractères spéciaux. 
	for (unsigned int i = 0; i < ligneCourante.length(); i++)
	{
		unsigned int ascii = ligneCourante[i];
		if (ascii >= 128)
		{
			cout << "La citation #" << noCitation << " contient des caractères non-valide.\n La phrase ne peut pas être traitée." << endl;
			system("pause");
			return false;
		}
	}
	return true;
}

void traiterSeparateurs(string& ligneCourante)
{
	for (int i = 0; i < ligneCourante.length() - 1; i++)
	{
		// Remplacer tout genre de punctuation par des espaces.
		if (!isalpha(ligneCourante[i]))
			ligneCourante[i] = ' ';
		
		// Si deux caractères de punctuation sont ensemble, on va créer deux sub-strings, excluant le deuxième.
		// On remplace la phrase originale avec les deux sub-strings concatinés.
		if (!isalpha(ligneCourante[i]) && !isalpha(ligneCourante[i + 1]))
		{
			string tempDebut = ligneCourante.substr(0, i);
			string tempFin = ligneCourante.substr(i + 1, ligneCourante.length());
			ligneCourante = tempDebut + tempFin;
		}
	}
	return;
}
