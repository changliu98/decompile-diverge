void cmatrix_to_frame(const double *m, double *v1, double *v2, double *v3)
{
    int i;
    for (i = 0; i < 3; i++) {
        v1[i] = m[i * 3];
        v2[i] = m[i * 3 + 1];
        v3[i] = m[i * 3 + 2];
    }
}