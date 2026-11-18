void pn_diag_SD_contr(int n, double *a, double *b, double *c) {
    while (n != 0) {
        *c = *a * *b + *c;
        a++;
        b++;
        c++;
        n--;
    }
}