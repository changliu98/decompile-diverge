void func0(char s1[], char s2[]) {
    int i, j, k;
    int c;

    for (i = j = 0; (c = s1[i])!= '\0'; i++) {
        for (k = 0; s2[k]!= '\0'; k++) {
            if (c == s2[k]) {
                c = 1;
                break;
            }
        }
        if (c == 0) {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';
}