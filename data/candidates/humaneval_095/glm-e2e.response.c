int func0(char **str_array, int n) {
    if (n == 0) {
        return 0;
    }

    int has_lower = 0;
    int has_upper = 0;

    for (int i = 0; i < n; i++) {
        char *s = str_array[i];
        for (int j = 0; s[j] != '\0'; j++) {
            if (!isalpha(s[j])) {
                return 0;
            }
            if (isupper(s[j])) {
                has_upper = 1;
            }
            if (islower(s[j])) {
                has_lower = 1;
            }
            if (has_upper + has_lower == 2) {
                return 0;
            }
        }
    }
    
    return 1;
}