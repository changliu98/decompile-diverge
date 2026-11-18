int filenvercmp(char *s1, long long int n1, char *s2, long long int n2) {
    long long int i, j, k, l, m, n, o, p;
    int res;
    while (1) {
        i = n1 > 0 && s1[0]!= '.' && s1[0]!= '\0';
        j = n2 > 0 && s2[0]!= '.' && s2[0]!= '\0';
        if (i && j) {
            k = strcmp(s1, s2);
            l = strcmp(s2, s1);
            m = k == 0 && l == 0;
            n = k == 0 || l == 0;
            o = k!= 0 && l!= 0;
            if (o) {
                res = k;
            } else if (n) {
                res = 1;
            } else {
                res = strcmp(s1, s2);
            }
        } else if (i) {
            res = 1;
        } else if (j) {
            res = -1;
        } else {
            break;
        }
    }
    return res;
}