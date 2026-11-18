void func0(int n, double *px, double *py, double *pz) {
    do {
        *(py++) += (*(px++)) * (*(pz++));
    } while (--n);
}