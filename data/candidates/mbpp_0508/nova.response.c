bool func0(char *s1[], char *s2[], int n1, int n2) {
    int i, j, k, l;
    char *s3[100], *s4[100];
    for (i = 0, k = 0; i < n1; i++) {
        for (j = 0, l = 0; j < n2; j++) {
            if (strcmp(s1[i], s2[j]) == 0) {
                bool x = true;
                for (int m = 0; m < k; m++) {
                    if (strcmp(s3[m], s1[i]) == 0) {
                        x = false;
                        break;
                    }
                }
                if (x) {
                    s3[k++] = s1[i];
                }
            }
        }
    }
    for (i = 0, l = 0; i < k; i++) {
        for (j = 0; j < l; j++) {
            if (strcmp(s4[j], s3[i]) == 0) {
                break;
            }
        }
        if (j == l) {
            s4[l++] = s3[i];
        }
    }
    return l % 2 == 1;
}