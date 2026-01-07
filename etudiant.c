#include "etudiant.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Vérifie si un matricule existe
int matriculeExiste(Etudiant *etudiants[], int nombre, char *matricule) {
    for (int i = 0; i < nombre; i++) {
        if (strcmp(etudiants[i]->matricule, matricule) == 0) 
        return 1;
    }
    return 0;
}

// Retourne l'année actuelle (2026)
int anneeActuelle() {
    return 2026; // Année fixe comme demandé
}

// Retourne l'année actuelle (2026)
int anneeActuelle() {
    return 2026; // Année fixe comme demandé
}

// Charge les étudiants depuis fichier
void chargerEtudiants(Etudiant *etudiants[], int *nombre) {
    FILE *f = fopen("etudiants.txt", "r");
    if (!f) return;
    
    *nombre = 0;
    while (*nombre < MAX_ETUDIANTS) {
        Etudiant *e = malloc(sizeof(Etudiant));
        if (!e) break;
        
        if (fscanf(f, "%14[^;];%49[^;];%49[^;];%d;%d;%d;%49[^;];%49[^;];%49[^\n]\n",
                  e->matricule, e->nom, e->prenom, &e->jour, &e->mois, &e->annee,
                  e->departement, e->region, e->filiere) != 9) {
            free(e);
            break;
        }
        
        etudiants[*nombre] = e;
        (*nombre)++;
    }
    fclose(f);
}

// Sauvegarde les étudiants dans fichier
void sauvegarderEtudiants(Etudiant *etudiants[], int nombre) {
    FILE *f = fopen("etudiants.txt", "w");
    if (!f) return;
    
    for (int i = 0; i < nombre; i++) {
        fprintf(f, "%s;%s;%s;%d;%d;%d;%s;%s;%s\n",
                etudiants[i]->matricule,
                etudiants[i]->nom,
                etudiants[i]->prenom,
                etudiants[i]->jour,
                etudiants[i]->mois,
                etudiants[i]->annee,
                etudiants[i]->departement,
                etudiants[i]->region,
                etudiants[i]->filiere);
    }
    fclose(f);
}

// Enregistre un nouvel étudiant
void enregistrerEtudiant(Etudiant *etudiants[], int *nombre) {
    if (*nombre >= MAX_ETUDIANTS) {
        printf("Limite d'etudiants atteinte\n");
        return;
    }
    
    Etudiant *e = malloc(sizeof(Etudiant));
    
    // Demander si étudiant nouveau ou ancien
    printf(" SI VOUS ETES NOUVEAU Etudiant ENTRE (N) OU SI VOUS ETES  ancien ENTRE (A) ? ");
    char type;
    scanf(" %c", &type);
    
    if (type == 'N' || type == 'n') {
        // Nouvel étudiant - générer matricule 26ENSPMETU001
        int num = *nombre + 1;
        do {
            sprintf(e->matricule, "26ENSPMETU%03d", num);
            num++;
        } while (matriculeExiste(etudiants, *nombre, e->matricule));
        printf("Matricule attribue: %s\n", e->matricule);
    } else {
        // Ancien étudiant - saisir matricule
        printf("Entrez votre matricule (ex: 25ENSPMETU001): ");
        scanf("%s", e->matricule);
        
        // Vérifier s'il existe déjà
        if (matriculeExiste(etudiants, *nombre, e->matricule)) {
            printf("Ce matricule existe deja!\n");
            free(e);
            return;
        }
    }
    
    // Saisie des informations
    printf("Nom: ");
    scanf("%s", e->nom);
    
    printf("Prenom: ");
    scanf("%s", e->prenom);
    
    // Saisie de la date avec validation
    printf("Date de naissance:\n");
    
    do {
        printf("  Jour (1-31): ");
        scanf("%d", &e->jour);
    } while (e->jour < 1 || e->jour > 31);
    
    do {
        printf("  Mois (1-12): ");
        scanf("%d", &e->mois);
    } while (e->mois < 1 || e->mois > 12);
    
    do {
        printf("  Annee (1900-2026): ");
        scanf("%d", &e->annee);
    } while (e->annee < 1900 || e->annee > 2026);
    
    printf("Departement: ");
    scanf("%s", e->departement);
    
    printf("Region: ");
    scanf("%s", e->region);
    
    // Choix de filière
    printf("Filiere (1-5):\n");
    printf("1. Reseau et Telecommunication\n");
    printf("2. Securite et Cryptographie\n");
    printf("3. Genie Logiciel\n");
    printf("4. Robotique et Systeme Embarque\n");
    printf("5. Data Science\n");
    printf("Choix: ");
    
    int choix;
    scanf("%d", &choix);
    
    switch(choix) {
        case 1: strcpy(e->filiere, "Reseau et Telecommunication"); break;
        case 2: strcpy(e->filiere, "Securite et Cryptographie"); break;
        case 3: strcpy(e->filiere, "Genie Logiciel"); break;
        case 4: strcpy(e->filiere, "Robotique et Systeme Embarque"); break;
        case 5: strcpy(e->filiere, "Data Science"); break;
        default: strcpy(e->filiere, "Non specifie");
    }
    
    // Ajout à la liste
    etudiants[*nombre] = e;
    (*nombre)++;
    printf("Etudiant enregistre avec succes\n");
}
