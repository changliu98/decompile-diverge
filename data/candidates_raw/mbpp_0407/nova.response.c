int func0(int n) {
    char s[MAXLEN], t[MAXLEN];
    int i, j, k, len;
    do {
        sprintf(s, "%d", n);
        len = strlen(s);
        for (i = len - 2; i >= 0; i--) {
            if (s[i] < s[i + 1]) {
                strcpy(t, s + i + 1);
                k = t[0];
                for (j = 1; j < strlen(t); j++) {
                    if (t[j] < k && t[j] > s[i]) {
                        k = t[j];
                        for (j = i + 1; j < strlen(t); j++)
                            s[j] = t[j];
                        s[len - 1] = '\0';
                        break;
                    }
                }
                s[i] = k;
                strcat(s + i + 1, t);
                return atoi(s);
            }
        }
    } while (1);
    return 0;
}