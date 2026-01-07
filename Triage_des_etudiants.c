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

}