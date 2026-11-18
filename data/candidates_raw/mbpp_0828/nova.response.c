void func0(char *str, int *vowels, int *consonants, int *digits) {
    int i = 0;
    *vowels = *consonants = *digits = 0;
    while (str[i]!= '\0') {
        if (isalpha(str[i])) {
            if (isVowel(str[i]))
                (*vowels)++;
            else if (isConsonant(str[i]))
                (*consonants)++;
        } else if (isdigit(str[i]))
            (*digits)++;
        i++;
    }
}