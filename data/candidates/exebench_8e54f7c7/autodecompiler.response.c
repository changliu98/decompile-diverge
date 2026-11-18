void cspline2bezier(
    double * restrict x,
    const double * restrict y
)
{
    double m[4][4];
    memset(m, 0, sizeof(m));
    m[0][0] = 1;
    m[0][1] = 1;
    m[1][1] = 1;
    m[1][2] = 1./3;
    m[2][2] = 1;
    m[2][3] = 1;
    m[3][3] = -1./3;

    int i, j;
    for (i = 0; i < 4; ++i) {
        if (i >= 4/2)
            break;
        x[i] = 0;
        for (j = 0; j < 4; ++j) {
            x[i] += m[j][i] * y[j];
        }
    }
}