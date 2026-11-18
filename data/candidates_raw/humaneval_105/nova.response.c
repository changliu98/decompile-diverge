void func0(int *a, int n, char **b, int *k) {
    char s[100];
    int i, j, t;
    do {
        strcpy(s, "");
        for (i = n - 1; i >= 0; i--) {
            if (a[i] < 2 && a[i + 1] >= 2) {
                t = a[i];
                a[i] = a[i + 1];
                a[i + 1] = t;
            } else {
                break;
            }
        }
        if (i < 0) {
            if (a[i] < 2 && a[i + 1] >= 2) {
                t = a[i];
                a[i] = a[i + 1];
                a[i + 1] = t;
            }
        }
    } while (i % 2 == 0);
    *b = (char *)malloc((*k) * sizeof(char));
    for (i = n - 1; i >= 0; i--) {
        if (i % 2 == 0) {
            strcat(*b, s);
        } else {
            strcat(*b, s);
        }
    }
}