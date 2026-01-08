#ifndef etudiant_H
#define etudiant_H

#define MAX_ETUDIANTS 100

// Structure d'un étudiant
typedef struct {
    char matricule[15];      // Format: 26ENSPMETU001
    char nom[50];           // Nom de l'étudiant
    char prenom[50];        // Prénom de l'étudiant
    int jour, mois, annee;  // Date de naissance séparée
    char departement[50];   // Département d'origine
    char region[50];        // Région d'origine
    char filiere[50];       // Filière choisie
} Etudiant;

// Fonctions principales
void chargerEtudiants(Etudiant *etudiants[], int *nombre);
void sauvegarderEtudiants(Etudiant *etudiants[], int nombre);
void enregistrerEtudiant(Etudiant *etudiants[], int *nombre);
void modifierEtudiant(Etudiant *etudiants[], int nombre);
void rechercherEtudiant(Etudiant *etudiants[], int nombre);
void supprimerEtudiant(Etudiant *etudiants[], int *nombre);
void trierAlphabetique(Etudiant *etudiants[], int nombre);
void rechercheDichotomique(Etudiant *etudiants[], int nombre);
void calculerAgeEtudiant(Etudiant *etudiants[], int nombre);
void trierParFiliere(Etudiant *etudiants[], int nombre);
void afficherTousEtudiants(Etudiant *etudiants[], int nombre);
void afficherMenu();

// Fonctions utilitaires
int matriculeExiste(Etudiant *etudiants[], int nombre, char *matricule);
int anneeActuelle();  // Retourne l'année actuelle (2026)

#endif