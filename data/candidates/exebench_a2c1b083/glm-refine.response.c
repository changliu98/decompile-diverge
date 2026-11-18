void __cdecl matmat3(double *A, double *B, double *C, double alpha, double beta)
{
    // Cast 1D arrays to 3x3 matrix representations for better readability
    double (*a)[3] = (double (*)[3])A;
    double (*b)[3] = (double (*)[3])B;
    double (*c)[3] = (double (*)[3])C;

    // Row 0
    c[0][0] = beta * c[0][0] + alpha * (a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0]);
    c[0][1] = beta * c[0][1] + alpha * (a[0][0] * b[0][1] + a[0][1] * b[1][1] + a[0][2] * b[2][1]);
    c[0][2] = beta * c[0][2] + alpha * (a[0][0] * b[0][2] + a[0][1] * b[1][2] + a[0][2] * b[2][2]);

    // Row 1
    c[1][0] = beta * c[1][0] + alpha * (a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0]);
    c[1][1] = beta * c[1][1] + alpha * (a[1][0] * b[0][1] + a[1][1] * b[1][1] + a[1][2] * b[2][1]);
    c[1][2] = beta * c[1][2] + alpha * (a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2]);

    // Row 2
    c[2][0] = beta * c[2][0] + alpha * (a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0]);
    c[2][1] = beta * c[2][1] + alpha * (a[2][0] * b[0][1] + a[2][1] * b[1][1] + a[2][2] * b[2][1]);
    c[2][2] = beta * c[2][2] + alpha * (a[2][0] * b[0][2] + a[2][1] * b[1][2] + a[2][2] * b[2][2]);
}