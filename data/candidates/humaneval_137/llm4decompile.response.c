char * func0(char * str0, char * str1) {
    char *end;
    char *s0 = strdup(str0);
    char *s1 = strdup(str1);
    for (int i = 0; s0[i] != '\0'; i++) {
        if (s0[i] == ',') {
            s0[i] = '.';
        }
    }
    for (int i = 0; s1[i] != '\0'; i++) {
        if (s1[i] == ',') {
            s1[i] = '.';
        }
    }
    double a = strtod(s0, &end);
    if (*end != '\0') {
        free(s0);
        free(s1);
        return "Invalid input";
    }
    double b = strtod(s1, &end);
    if (*end != '\0') {
        free(s0);
        free(s1);
        return "Invalid input";
    }
    free(s0);
    free(s1);
    if (a == b) {
        return "None";
    }
    return a > b ? str0 : str1;
}