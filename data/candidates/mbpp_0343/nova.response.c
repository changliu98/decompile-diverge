void func0(const char *str, int *vowels, int *consonants) {
    int v = 0, c = 0;
    while (*str) {
        if (isVowel(str))
            v++;
        else if (isConsonant(str))
            c++;
        str++;
    }
    *vowels = v;
    *consonants = c;
}