// Calcule l'âge d'un étudiant
void calculerAgeEtudiant(Etudiant *etudiants[], int nombre) {
    char matricule[15];
    printf("Matricule de l'etudiant: ");
    scanf("%s", matricule);
    
    //test si l'étudiant existe
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