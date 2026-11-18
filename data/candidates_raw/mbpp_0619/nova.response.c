char *func0(char *s) {
    int i = 0;
    int j = 0;
    int k = 0;
    char temp[1001];
    while (1) {
        if (s[k]!= '\0') {
            if (isalpha(s[k])) {
                temp[j++] = s[k];
            } else {
                a[i++] = s[k];
            }
        } else {
            break;
        }
        k++;
    }
    temp[j] = '\0';
    a[i] = '\0';
    strcat(b, temp);
    return c;
}