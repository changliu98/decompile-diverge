int func0(char *s) {
    int i, len, count = 0;
    char *vowels = "aeiou";
    len = strlen(s);
    for (i = 1; i < len - 1; i++) {
        if (strchr(vowels, s[i]) && strchr(vowels, s[i - 1]) == NULL &&
            strchr(vowels, s[i + 1]) == NULL) {
            count++;
        }
    }
    if (strchr(vowels, s[0]) == NULL && strchr(vowels, s[1])!= NULL)
        count++;
    if (strchr(vowels, s[len - 1]) == NULL && strchr(vowels, s[len - 2])!= NULL)
        count++;
    return count;
}