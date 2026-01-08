void calculAge(int birthYear, int currentYear, int *age) {
    if (age != NULL) {
        *age = currentYear - birthYear;
    }
}