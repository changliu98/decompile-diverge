int func0(char *s) {
    char *vowels = "aeiou";
    int i, j, k, l, m, n;

    n = strlen(s);
    m = 0;
    for (i = 0; i < n; i++) {
        if (strchr(vowels, s[i]))
            m++;
        else
            i++;
    }
    if (n > 0 && (s[n - 1] == 'y' || s[n - 1] == 'Y'))
        m++;

    return m;
}