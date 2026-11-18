int func0(char *s) {
    char *p = vowels;
    int count = 0;
    int i = 0;
    bool is_vowel;

    while (true) {
        is_vowel = false;
        if (s[i]!= '\0') {
            is_vowel = (strchr(p, s[i])!= NULL);
        }

        if (is_vowel) {
            if (is_vowel) {
                count++;
            }
        } else {
            i++;
        }
    }

    return count;
}