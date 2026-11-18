const char* func0(const char *str) {
    int digits = 0;
    int dots = 0;
    int len = strlen(str);

    if (len < 5) {
        return "False";
    }

    char first = str[0];
    if (!((first >= 'A' && first <= 'Z') || (first >= 'a' && first <= 'z'))) {
        return "False";
    }

    const char *suffix = str + len - 4;
    if (strcmp(suffix, ".txt") != 0 && 
        strcmp(suffix, ".exe") != 0 && 
        strcmp(suffix, ".pdf") != 0) {
        return "False";
    }

    for (int i = 0; i < len; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            digits++;
        }
        if (str[i] == '.') {
            dots++;
        }
    }

    if (digits > 3 && dots == 1) {
        return "True";
    }

    return "False";
}