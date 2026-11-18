void reverse(char s[]) {
    int i, max;
    char c;

    for (i = 0; s[i] != '\0'; ++i);
    max = i;
    for (i = 0; i < max / 2; ++i) {
        c = s[i];
        s[i] = s[max - (i + 1)];
        s[max - (i + 1)] = c;
    }
}