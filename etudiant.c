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

// Modifie un étudiant
void modifierEtudiant(Etudiant *etudiants[], int nombre) {
    char matricule[15];
    printf("Matricule de l'etudiant a modifier: ");
    scanf("%s", matricule);
    
    for (int i = 0; i < nombre; i++) {
        if (strcmp(etudiants[i]->matricule, matricule) == 0) {
            printf("Que modifier? (1-Nom 2-Prenom 3-Date 4-Departement 5-Region 6-Filiere): ");
            int choix;
            scanf("%d", &choix);
            
            switch(choix) {
                case 1:
                    printf("Nouveau nom: ");
                    scanf("%s", etudiants[i]->nom);
                    break;
                case 2:
                    printf("Nouveau prenom: ");
                    scanf("%s", etudiants[i]->prenom);
                    break;
                case 3:
                    printf("Nouvelle date:\n");
                    do {
                        printf("  Jour (1-31): ");
                        scanf("%d", &etudiants[i]->jour);
                    } while (etudiants[i]->jour < 1 || etudiants[i]->jour > 31);
                    do {
                        printf("  Mois (1-12): ");
                        scanf("%d", &etudiants[i]->mois);
                    } while (etudiants[i]->mois < 1 || etudiants[i]->mois > 12);
                    do {
                        printf("  Annee (1900-2026): ");
                        scanf("%d", &etudiants[i]->annee);
                    } while (etudiants[i]->annee < 1900 || etudiants[i]->annee > 2026);
                    break;
                case 4:
                    printf("Nouveau departement: ");
                    scanf("%s", etudiants[i]->departement);
                    break;
                case 5:
                    printf("Nouvelle region: ");
                    scanf("%s", etudiants[i]->region);
                    break;
                case 6:
                    printf("Nouvelle filiere (1-5): ");
                    int f;
                    scanf("%d", &f);
                    if (f == 1) strcpy(etudiants[i]->filiere, "Reseau et Telecommunication");
                    else if (f == 2) strcpy(etudiants[i]->filiere, "Securite et Cryptographie");
                    else if (f == 3) strcpy(etudiants[i]->filiere, "Genie Logiciel");
                    else if (f == 4) strcpy(etudiants[i]->filiere, "Robotique et Systeme Embarque");
                    else if (f == 5) strcpy(etudiants[i]->filiere, "Data Science");
                    break;
                default:
                    printf("Choix invalide\n");
                    return;
            }
            printf("Modification reussie\n");
            return;
        }
    }
    printf("Etudiant non trouve\n");
}

// Recherche un étudiant
void rechercherEtudiant(Etudiant *etudiants[], int nombre) {
    char nom[50];
    printf("Nom a rechercher: ");
    scanf("%s", nom);
    
    int trouve = 0;
    for (int i = 0; i < nombre; i++) {
        if (strcmp(etudiants[i]->nom, nom) == 0) {
            printf("\nMatricule: %s\n", etudiants[i]->matricule);
            printf("Nom: %s\n", etudiants[i]->nom);
            printf("Prenom: %s\n", etudiants[i]->prenom);
            printf("Date: %02d/%02d/%04d\n", etudiants[i]->jour, etudiants[i]->mois, etudiants[i]->annee);
            printf("Departement: %s\n", etudiants[i]->departement);
            printf("Region: %s\n", etudiants[i]->region);
            printf("Filiere: %s\n", etudiants[i]->filiere);
            trouve = 1;
        }
    }
    if (!trouve) printf("Aucun etudiant CORRESPONDANT A CETTE RECHERCHE N'AS ETE trouve\n");
}

// Supprime un étudiant
void supprimerEtudiant(Etudiant *etudiants[], int *nombre) {
    char matricule[15];
    printf("Matricule de l'etudiant a supprimer: ");
    scanf("%s", matricule);
    
    for (int i = 0; i < *nombre; i++) {
        if (strcmp(etudiants[i]->matricule, matricule) == 0) {
            free(etudiants[i]);
            for (int j = i; j < *nombre - 1; j++) {
                etudiants[j] = etudiants[j + 1];
            }
            (*nombre)--;
            printf("NOUS AVONS SUPPRIMER CETTE ETUDIANT\n");
            return;
        }
    }
    printf("Etudiant non trouve\n");
}


// Trie par ordre alphabétique et AFFICHE le résultat
void trierAlphabetique(Etudiant *etudiants[], int nombre) {
    // Vérifier s'il y a des étudiants
    if (nombre == 0) {
        printf("Aucun etudiant a trier\n");
        return;
    }
    
    // Tri à bulles par nom
    for (int i = 0; i < nombre - 1; i++) {
        for (int j = 0; j < nombre - i - 1; j++) {
            if (strcmp(etudiants[j]->nom, etudiants[j+1]->nom) > 0) {
                Etudiant *temp = etudiants[j];
                etudiants[j] = etudiants[j+1];
                etudiants[j+1] = temp;
            }
        }
    }
    
    printf("\n=== LISTE TRIEE PAR ORDRE ALPHABETIQUE ===\n");
    
    // En-tête du tableau
    printf("\n+---------------+---------------+---------------+---------------+\n");
    printf("| Matricule     | Nom           | Prenom        | Filiere       |\n");
    printf("+---------------+---------------+---------------+---------------+\n");
    
    // Afficher les étudiants triés
    for (int i = 0; i < nombre; i++) {
        printf("| %-13s | %-13s | %-13s | %-13s |\n",
               etudiants[i]->matricule,
               etudiants[i]->nom,
               etudiants[i]->prenom,
               etudiants[i]->filiere);
    }
    
    printf("+---------------+---------------+---------------+---------------+\n");
    printf("Total: %d etudiant(s)\n", nombre);
}

// Recherche dichotomique
void rechercheDichotomique(Etudiant *etudiants[], int nombre) {
    if (nombre == 0) {
        printf("Liste vide\n");
        return;
    }
    
    // Vérifier si liste triée
    int estTrie = 1;
    for (int i = 0; i < nombre - 1; i++) {
        if (strcmp(etudiants[i]->nom, etudiants[i+1]->nom) > 0) {
            estTrie = 0;
            break;
        }
    }
    
    if (!estTrie) {
        printf("Liste non triee, tri en cours...\n");
        
        // Tri sans affichage pour la recherche dichotomique
        for (int i = 0; i < nombre - 1; i++) {
            for (int j = 0; j < nombre - i - 1; j++) {
                if (strcmp(etudiants[j]->nom, etudiants[j+1]->nom) > 0) {
                    Etudiant *temp = etudiants[j];
                    etudiants[j] = etudiants[j+1];
                    etudiants[j+1] = temp;
                }
            }
        }
    }
    
    char nom[50];
    printf("Nom a rechercher: ");
    scanf("%s", nom);
    
    int debut = 0, fin = nombre - 1;
    while (debut <= fin) {
        int milieu = (debut + fin) / 2;
        int cmp = strcmp(etudiants[milieu]->nom, nom);
        
        if (cmp == 0) {
            printf("\nEtudiant trouve:\n");
            printf("Matricule: %s\n", etudiants[milieu]->matricule);
            printf("Nom: %s\n", etudiants[milieu]->nom);
            printf("Prenom: %s\n", etudiants[milieu]->prenom);
            printf("Date: %02d/%02d/%04d\n", etudiants[milieu]->jour, etudiants[milieu]->mois, etudiants[milieu]->annee);
            printf("Filiere: %s\n", etudiants[milieu]->filiere);
            return;
        } else if (cmp < 0) {
            debut = milieu + 1;
        } else {
            fin = milieu - 1;
        }
    }
    printf("Etudiant non trouve\n");
}

// Calcule l'âge d'un étudiant
void calculerAgeEtudiant(Etudiant *etudiants[], int nombre) {
    char matricule[15];
    printf("Matricule de l'etudiant: ");
    scanf("%s", matricule);
    
    for (int i = 0; i < nombre; i++) {
        if (strcmp(etudiants[i]->matricule, matricule) == 0) {
            int age = anneeActuelle() - etudiants[i]->annee;
            printf("%s %s a %d ans (ne(e) en %d)\n", 
                   etudiants[i]->prenom, etudiants[i]->nom, age, etudiants[i]->annee);
            return;
        }
    }
    printf("Etudiant non trouve\n");
}

// Trie par filière et AFFICHE le résultat
void trierParFiliere(Etudiant *etudiants[], int nombre) {
    // Vérifier s'il y a des étudiants
    if (nombre == 0) {
        printf("Aucun etudiant a trier\n");
        return;
    }
    
    // Tri par filière (puis par nom si même filière)
    for (int i = 0; i < nombre - 1; i++) {
        for (int j = 0; j < nombre - i - 1; j++) {
            int cmp = strcmp(etudiants[j]->filiere, etudiants[j+1]->filiere);
            if (cmp > 0 || (cmp == 0 && strcmp(etudiants[j]->nom, etudiants[j+1]->nom) > 0)) {
                Etudiant *temp = etudiants[j];
                etudiants[j] = etudiants[j+1];
                etudiants[j+1] = temp;
            }
        }
    }
    
    printf("\n=== LISTE TRIEE PAR FILIERE ===\n");
    
    // En-tête du tableau
    printf("\n+---------------+---------------+---------------+---------------+\n");
    printf("| Filiere                    | Nom           | Prenom        | Matricule     |\n");
    printf("+----------------------------+---------------+---------------+---------------+\n");
    
    // Afficher les étudiants triés
    for (int i = 0; i < nombre; i++) {
        printf("| %-26s | %-13s | %-13s | %-13s |\n",
               etudiants[i]->filiere,
               etudiants[i]->nom,
               etudiants[i]->prenom,
               etudiants[i]->matricule);
    }
    
    printf("+----------------------------+---------------+---------------+---------------+\n");
    printf("Total: %d etudiant(s)\n", nombre);
}

// Affiche tous les étudiants dans un tableau
void afficherTousEtudiants(Etudiant *etudiants[], int nombre) {
    if (nombre == 0) {
        printf("Aucun etudiant\n");
        return;
    }
    
    printf("\n+---------------+---------------+---------------+---------------+---------------+---------------+-------------------------+\n");
    printf("| Matricule     | Nom           | Prenom        | Date naiss.   | Departement   | Region        | Filiere                 |\n");
    printf("+---------------+---------------+---------------+---------------+---------------+---------------+-------------------------+\n");
    
    // Données
    for (int i = 0; i < nombre; i++) {
        char date[11];
        sprintf(date, "%02d/%02d/%04d", etudiants[i]->jour, etudiants[i]->mois, etudiants[i]->annee);
        
        printf("| %-13s | %-13s | %-13s | %-13s | %-13s | %-13s | %-23s |\n",
               etudiants[i]->matricule,
               etudiants[i]->nom,
               etudiants[i]->prenom,
               date,
               etudiants[i]->departement,
               etudiants[i]->region,
               etudiants[i]->filiere);
    }
    
    // Bas du tableau
    printf("+---------------+---------------+---------------+---------------+---------------+---------------+-------------------------+\n");
    printf("Total: %d etudiant(s)\n", nombre);
}
// Affiche le menu principal
void afficherMenu() {
    printf("\n PROJET C GESTION DES ETUTIANTS  GROUPE 4 : MENU PRINCIPAL \n");
    printf("1. Enregistrer un etudiant\n");
    printf("2. Modifier un etudiant\n");
    printf("3. Rechercher un etudiant\n");
    printf("4. Supprimer un etudiant\n");
    printf("5. Trier par ordre alphabetique\n");
    printf("6. Recherche dichotomique\n");
    printf("7. Calcul de l'age de l'etudiant\n");
    printf("8. Trier par filiere\n");
    printf("9. Afficher la liste complete des etudiants\n");
    printf("10. Sauvegarder et quitter\n");
    printf("QUELLE OPTION DU MENU VOUS INTERESSE: ");
}
