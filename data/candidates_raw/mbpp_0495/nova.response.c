char *func0(char *s) {
    int i, j;
    i = j = 0;
    while (1) {
        if (s[i]!= '\0') {
            if (s[i] >= 'a' && s[i] <= 'z') {
                vowels[j++] = s[i];
            }
        } else {
            break;
        }
        i++;
    }
    vowels[j] = '\0';
    return vowels;
}