char *func0(char *s) {
    int i = 0, j = 0;
    while (j < strlen(s)) {
        if (isalpha(s[j])) {
            vowels[i++] = s[j];
        }
        j++;
    }
    vowels[i] = '\0';
    return vowels;
}