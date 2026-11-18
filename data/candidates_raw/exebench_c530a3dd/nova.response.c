int func0(char *s, char *t) {
    int i = 0;
    int j = 0;
    int k = 0;
    while (1) {
        s[i] = t[j];
        if (s[i] == '\0') {
            k = i;
            break;
        }
        i++;
        j++;
        k++;
        s[i] = t[j];
        if (s[i] == '\0') {
            k = i;
            break;
        }
        i++;
        j++;
        k++;
        s[i] = t[j];
        if (s[i] == '\0') {
            k = i;
            break;
        }
        i++;
        j++;
        k++;
    }
    return k;
}