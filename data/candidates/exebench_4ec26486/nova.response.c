void squeeze_all(char s1[], char s2[]) {
    int i, j, k;
    bool equalStrings;

    i = j = k = 0;

    while (s1[i]!= '\0') {
        equalStrings = false;
        for (j = 0; s2[j]!= '\0'; j++) {
            if (s1[i] == s2[j]) {
                equalStrings = true;
            }
        }
        if (!equalStrings) {
            s1[k++] = s1[i];
        }
        i++;
    }
    s1[k] = '\0';
}