void func0(char *s) {
    int i = 0, j = 0;
    char *vowel = "aeiou";
    char *consonant = "bcdfghjklmnpqrstvwxyz";
    while (1) {
        if (s[i] == '\0')
            break;
        for (j = 0; j < 5; j++) {
            if (s[i] == vowel[j]) {
                s[i] = vowel[j + 1];
                break;
            }
            if (s[i] == consonant[j]) {
                s[i] = consonant[j + 1];
                break;
            }
        }
        i++;
    }
}