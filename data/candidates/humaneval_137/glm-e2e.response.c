const char* func0(const char* arg1, const char* arg2) {
    char* s1 = strdup(arg1);
    char* s2 = strdup(arg2);

    for (int i = 0; s1[i] != '\0'; i++) {
        if (s1[i] == ',') {
            s1[i] = '.';
        }
    }

    for (int i = 0; s2[i] != '\0'; i++) {
        if (s2[i] == ',') {
            s2[i] = '.';
        }
    }

    char* endptr1;
    double val1 = strtod(s1, &endptr1);
    if (*endptr1 != '\0') {
        free(s1);
        free(s2);
        return "Invalid"; // 0x2004
    }

    char* endptr2;
    double val2 = strtod(s2, &endptr2);
    if (*endptr2 != '\0') {
        free(s1);
        free(s2);
        return "Invalid"; // 0x2004
    }

    free(s1);
    free(s2);

    if (val1 == val2) {
        return "Equal"; // 0x2012
    } else if (val1 > val2) {
        return arg1;
    } else {
        return arg2;
    }
}