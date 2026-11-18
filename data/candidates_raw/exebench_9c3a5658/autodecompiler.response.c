void mat3_diag(double *A, double *a, double *b, double *c)
{
    int i;
    for (i=0; i<3; i++) {
        A[3*i + 0] = a[i];
        A[3*i + 1] = b[i];
        A[3*i + 2] = c[i];
    }
}