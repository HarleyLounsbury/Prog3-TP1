// Fonctions.h
// En-tête du fichier de fonctions pour "Citation Mystère".
//
// Auteur: Harley Lounsbury
// Date: 2019-09-06

#include "Biblio.h"

// Constantes.
const int MIN_LIGNE = 13;
const int MAX_LIGNE = 17;
const int MIN_CHAR_CITATION = 35;
const int MAX_CHAR_CITATION = 100;


void saisirNomFichierSource(string& nomFichierSource);
void traitementCitation(string ligneCourante, int noCitation);
void afficherHaut(string ligneCourante, int longeurLigne, int noCitation);
int determinerLongeurLigne(string ligneCourante);
int aleatoire(const int iMIN, const int iMAX);
void permuterAleatoire(string& temp);
void convertirMajuscule(string& phrase);
void melangerString(string& ligneCourante, int longeurLigne);
void afficherBas(string ligneCourante, int longeurLigne, ostream& of);
void ajouterEspaces(string& ligneCourante, int longeurLigne);
void afficherPhrase(string ligneCourante, int longeurLigne, ostream& of);
void permuterEspaces(string& temp);
void ecrireDansFichier(string ligneCourante, int longeurLigne, int noCitation, string copieOriginale);
bool validerLongeurString(string ligneCourante, int noCitation);
bool validerStringASCII(string ligneCourante, int noCitation);
void traiterSeparateurs(string& ligneCourante);