void func0(char *s) {
    int i, j;
    for (i = 0;; i++) {
        for (j = 0;; j++) {
            if (s[i] == vowels[j]) {
                break;
            }
            if (vowels[j] == '\0') {
                goto end;
            }
        }
        if (s[i] == vowels[j]) {
            s[i] = vowel_num[j];
        }
    end:
        if (s[i] == '\0') {
            break;
        }
    }
}