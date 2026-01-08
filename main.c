#include "etudiant.h"
#include <stdio.h>
#include <stdlib.h>

// Fonction principale
int main() {
    Etudiant *etudiants[MAX_ETUDIANTS];  // Tableau d'étudiants
    int nombreEtudiants = 0;             // Nombre actuel d'étudiants
    int choix;                           // Choix de l'utilisateur
    
    // Charger les données au démarrage
    chargerEtudiants(etudiants, &nombreEtudiants);
    
    // Boucle principale
    do {
        afficherMenu();
        scanf("%d", &choix);
        
        // Vider le buffer d'entrée
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        // Exécuter la fonction choisie
        switch(choix) {
            case 1: enregistrerEtudiant(etudiants, &nombreEtudiants); break;
            case 2: modifierEtudiant(etudiants, nombreEtudiants); break;
            case 3: rechercherEtudiant(etudiants, nombreEtudiants); break;
            case 4: supprimerEtudiant(etudiants, &nombreEtudiants); break;
            case 5: trierAlphabetique(etudiants, nombreEtudiants); break;
            case 6: rechercheDichotomique(etudiants, nombreEtudiants); break;
            case 7: calculerAgeEtudiant(etudiants, nombreEtudiants); break;
            case 8: trierParFiliere(etudiants, nombreEtudiants); break;
            case 9: afficherTousEtudiants(etudiants, nombreEtudiants); break;
            case 10: 
                sauvegarderEtudiants(etudiants, nombreEtudiants);
                printf("Donnees sauvegardees. Au revoir!\n");
                break;
            default: printf("Choix invalide\n");
        }
        
        // Pause entre les actions
        if (choix != 10) {
            printf("\nAppuyez sur Entree pour continuer...");
            getchar();
        }
        
    } while (choix != 10);
    
    // Libérer la mémoire
    for (int i = 0; i < nombreEtudiants; i++) {
        free(etudiants[i]);
    }
    
    return 0;
}