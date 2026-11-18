void extract(char *str, int len, int a, int b, int c, int *res) {
    int i, j, k;
    *res = 0;
    res[0] = 0;
    for (i = 0; i < a; i++) {
        for (j = 1; j < b; j++) {
            for (k = 1; k < c; k++) {
                if (str[i] == '(' && str[j] == ')' && str[k] == '*') {
                    res[0] = i;
                    res[1] = j - i;
                }
            }
        }
    }
}