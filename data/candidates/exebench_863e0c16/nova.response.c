void reverse(char *s) {
    int i, j;
    char temp;
    for (i = 0;; i++) {
        if (s[i] == '\0')
            break;
        if (s[i]!= '\n')
            continue;
    }
    for (j = i - 1; j >= 0; j--) {
        temp = s[j];
        s[j] = s[i];
        s[i] = temp;
        i--;
    }
}