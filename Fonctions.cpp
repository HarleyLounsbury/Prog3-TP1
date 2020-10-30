// Fonctions.cpp
// Fichier de fonctions pour "Citation Myst�re".
//
// Auteur: Harley Lounsbury
// Date: 2019-09-06

#include "Fonctions.h"

void saisirNomFichierSource(string& nomFichierSource)
{
	// Afficher le titre et demander le nom du fichier source.
	cout << "Bienvenue au jeu de Citation Myst�re" << endl;
	cout << "Veuillez entrer le nom du fichier source: ";
	getline(cin, nomFichierSource);

	return;
}

void traitementCitation(string ligneCourante, int noCitation)
{
	// �ffectuer des v�rifications sur la ligne.
	if (!validerStringASCII(ligneCourante, noCitation))
		return;

	if (!validerLongeurString(ligneCourante, noCitation))
		return;

	// S'occuper des s�parateurs adjacent.
	traiterSeparateurs(ligneCourante);

	// D�terminer le longeur optimale de chaque ligne, pour en avoir le moins de mots tronqu�s.
	int longeurLigne = determinerLongeurLigne(ligneCourante);

	// Convertir tous les caract�res en majuscule.
	convertirMajuscule(ligneCourante);

	// Afficher la citation, m�lang�e.
	afficherHaut(ligneCourante, longeurLigne, noCitation);

	// Afficher les espaces o� vont les caract�res.
	afficherBas(ligneCourante, longeurLigne, cout);

	// Message pour indiquer que la traitement a termin�e.
	cout << "Le fichier 'citation" << noCitation << ".txt' � �t� cr�� dans le dossier actuel." << endl;
	system("pause");

	return;
}

void afficherHaut(string ligneCourante, int longeurLigne, int noCitation)
{
	// Cr�er une copie de la phrase originale, pour conserver le placement des caract�res (car on va monter les lettres afficher en haut de la grille)
	string copieOriginal = ligneCourante;

	// Ajouter des espaces pour simuler un tableau. (peut-�tre pas n�cessaire, � v�rifier).
	ajouterEspaces(ligneCourante, longeurLigne);

	// M�langer les lettres en colonne.
	melangerString(ligneCourante, longeurLigne);

	// Afficher la phrase melang�e.
	afficherPhrase(ligneCourante, longeurLigne, cout);

	// �crire la m�me phrase melang�e dans le fichier.
	// Important d'�crire dans le fichier ici: les colonnes m�lang�es doit �tre pareilles que qu'est-ce qu'il est affich� � l'�cran.
	ecrireDansFichier(ligneCourante, longeurLigne, noCitation, copieOriginal);
		
	cout << setw(longeurLigne * 3 - 2) << setfill('-') << "-" << setfill(' ') << endl;

	return;
}

int determinerLongeurLigne(string ligneCourante)
{
	// Ancre pour m�moriser le longeur avec le moins de mots tronqu�s.
	int ancre = 0;
	// On commence le longeur par le minimum.
	int longeurLigne = MIN_LIGNE;
	// Boucle pour parcourir les possibilit�s de longeur de ligne.
	for (int i = MIN_LIGNE; i <= MAX_LIGNE; i++)
	{
		// Pour chaque longeur de ligne, on doit m�moriser le nombre de mots qui sont tronqu�s.
		int compteurMotsTronques = 0;
		// On doit v�rifier que si le premier caract�re d'une ligne est alphanum�rique et le dernier de la ligne pr�cedente, 
		// on consid�re que le mot est tronqu�. On augmente le compteur.
		for (int j = MIN_LIGNE; j < ligneCourante.length(); j += i)
		{
			if (isalpha(ligneCourante[j]) && isalpha(ligneCourante[j - 1]))
				compteurMotsTronques++;
		}
		// Si on est dans la premi�re it�ration, c'est le longeur optimale.
		if (i == MIN_LIGNE)
			ancre = compteurMotsTronques;
		// Si on voit qu'une longeur fait moins de mots tronqu�s, on remplace l'ancre et le longeur optimale.
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
	// G�n�rer le nombre au hasard, compris entre les limites fournies. 
	return rand() % (iMAX - iMIN + 1) + iMIN;
}

void permuterAleatoire(string& temp)
{
	// Variables locales.
	char tempChar;
	int position1;
	int position2;

	// Boucle pour permuter deux caract�res choisis al�atoirement.
	// On �ffectue les permutations 10 fois. Arbitraire, mais suffisant pour nos besoins.
	for (int i = 0; i < 10; i++)
	{
		position1 = aleatoire(0, temp.length() - 1);
		position2 = aleatoire(0, temp.length() - 1);
		
		tempChar = temp[position1];
		temp[position1] = temp[position2];
		temp[position2] = tempChar;
	}
	
	// Permuter les espaces � la fin de chaque cha�ne qui fait une colonne.
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
	// M�langer les lettres, une colonne � la fois.
	for (int i = 0; i < longeurLigne; i++)
	{
		temp = "";
		// Chercher les lettres d'une colonne.
		for (int j = i; j < ligneCourante.length(); j += longeurLigne)
		{
			temp += ligneCourante[j];
		}
		// M�langer le string temporaire.
		permuterAleatoire(temp);

		// Remettre les caract�res du string temporaire aux bons endroits.
		for (int j = i, k = 0; j < ligneCourante.length(); j += longeurLigne, k++)
		{
			ligneCourante[j] = temp[k];
		}
	}
	return;
}

void afficherBas(string ligneCourante, int longeurLigne, ostream& of)
{
	// Ajouter des espaces pour faire une grille pleine. (peut-�tre pas n�cessaire. � v�rifier)
	ajouterEspaces(ligneCourante, longeurLigne);

	// Boucle d'affichage. 
	for (int i = 0; i < ligneCourante.length(); i++)
	{
		// Passe � la ligne, selon le longeur optimale.
		if (i != 0 && i % longeurLigne == 0)
			of << endl;

		// Pour chaque caract�re alphanum�rique, imprimer _ � sa place, autrement, une espace.
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
	// Ajouter des espaces � la fin pour faire une grille pleine.
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
	// Afficher la phrase caract�re par caract�re avec deux espaces entre chaque.
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

	// Trier le string temporaire pour mettre les espaces � la fin (les caract�res seront en haut des colonnes).
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
	// Faire le m�me travail que l'affichage � l'�cran, mais dans le fichier. 
	string nomFichierOut = "citation" + to_string(noCitation) + ".txt";
	ofstream fichierOut(nomFichierOut, ios::app);
	afficherPhrase(ligneCourante, longeurLigne, fichierOut);
	afficherBas(copieOriginale, longeurLigne, fichierOut);
	
	fichierOut.close();

	return;
}

bool validerLongeurString(string ligneCourante, int noCitation)
{
	// V�rifier le longeur de la phrase contre le minimum et maximum nombre de caract�res.
	// Afficher le message d'erreur appropri�.
	if (ligneCourante.length() < MIN_CHAR_CITATION)
	{
		cout << "La citation #" << noCitation << " ne peut pas �tre trait�e car elle est tr�p courte." << endl;
		system("pause"); 
		return false;
	}
	if (ligneCourante.length() > MAX_CHAR_CITATION)
	{
		cout << "La citation #" << noCitation << " ne peut pas �tre trait�e car elle est tr�p longue." << endl;
		system("pause");
		return false;
	}

	return true;
}

bool validerStringASCII(string ligneCourante, int noCitation)
{
	// V�rifier qu'il n'y a pas de caract�res sp�ciaux. 
	for (unsigned int i = 0; i < ligneCourante.length(); i++)
	{
		unsigned int ascii = ligneCourante[i];
		if (ascii >= 128)
		{
			cout << "La citation #" << noCitation << " contient des caract�res non-valide.\n La phrase ne peut pas �tre trait�e." << endl;
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
		
		// Si deux caract�res de punctuation sont ensemble, on va cr�er deux sub-strings, excluant le deuxi�me.
		// On remplace la phrase originale avec les deux sub-strings concatin�s.
		if (!isalpha(ligneCourante[i]) && !isalpha(ligneCourante[i + 1]))
		{
			string tempDebut = ligneCourante.substr(0, i);
			string tempFin = ligneCourante.substr(i + 1, ligneCourante.length());
			ligneCourante = tempDebut + tempFin;
		}
	}
	return;
}
