char *func0(char *str) {
    int i, j, k, l, m, n;

    n = strlen(str);
    for (i = 0, j = 0; i < n; i++) {
        if (isalpha(str[i])) {
            if (islower(str[i]))
                str[i] = toupper(str[i]);
            else if (isupper(str[i]))
                str[i] = tolower(str[i]);
        }
    }
    if (n == i) {
        for (k = 0, l = i; k < i / 2; k++) {
            m = str[k];
            str[k] = str[i - k - 1];
            str[i - k - 1] = m;
        }
    }
    return str;
}