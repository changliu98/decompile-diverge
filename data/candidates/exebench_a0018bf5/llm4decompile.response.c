void innerdct(double *a, double *b, double *c)
{
    double a0, a1, a2, a3, a4, a5, a6, a7;
    double b0, b1, b2, b3, b4, b5, b6, b7;
    double c0, c1, c2, c3, c4, c5, c6, c7;

    a0 = a[0];
    a1 = a[1];
    a2 = a[2];
    a3 = a[3];
    a4 = a[4];
    a5 = a[5];
    a6 = a[6];
    a7 = a[7];

    c0 = c[0];
    c1 = c[1];
    c2 = c[2];
    c3 = c[3];
    c4 = c[4];
    c5 = c[5];
    c6 = c[6];
    c7 = c[7];

    b0 = (a0 + a7) + (a2 + a5);
    b1 = (a1 + a6) + (a3 + a4);
    b2 = (a1 + a6) - (a3 + a4);
    b3 = (a0 - a7) + (a2 - a5);
    b4 = (a0 - a7) - (a2 - a5);
    b5 = (a1 - a6) + (a3 - a4);
    b6 = (a1 - a6) - (a3 - a4);
    b7 = (a0 + a7) - (a2 + a5);

    b[0] = c4 * b0 + c4 * b1;
    b[16] = c4 * b0 - c4 * b1;
    b[8] = c2 * b7 + c6 * b3;
    b[24] = c6 * b7 - c2 * b3;
    b[4] = c7 * b6 + c5 * b2 + c1 * b4 + c3 * b5;
    b[20] = -c5 * b6 - c7 * b2 + c1 * b5 - c3 * b4;
    b[12] = c3 * b6 + c7 * b2 + c5 * b4 + -c1 * b5;
    b[28] = -c3 * b6 + c7 * b2 + c1 * b4 + -c5 * b5;
}