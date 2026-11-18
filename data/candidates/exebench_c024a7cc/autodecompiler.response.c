void pn_diag_SD_contr(int n, double *x, double *y, double *z)
{
    do {
        *y++ += (*z++) * (*x++);
    } while (--n);
}