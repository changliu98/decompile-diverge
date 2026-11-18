void pn_diag_SD_contr(int n, double *px, double *py, double *pz) {
    do {
        *(py++) += (*(px++)) * (*(pz++));
    } while (--n);
}