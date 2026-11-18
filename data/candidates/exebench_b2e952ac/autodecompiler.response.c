void ZVdotU32( const int M, const double *A, const double *B, double *C, const double *D, const double *E, double *sums )
{
    double _r00 = 0; double _i00 = 0;
    double _r01 = 0; double _i01 = 0;
    double _r10 = 0; double _i10 = 0;
    double _r11 = 0; double _i11 = 0;
    double _r20 = 0; double _i20 = 0;
    double _r21 = 0; double _i21 = 0;

    int k = 0;
    int k_iter = 0;
    int k_stop = 0;

    while (k < M)
    {
        double a_r0 = A[0];
        double a_i0 = A[1];

        double b_r0 = B[0];
        double b_i0 = B[1];

        double a_r1 = A[2];
        double a_i1 = A[3];

        double b_r1 = B[2];
        double b_i1 = B[3];

        double d_r0 = D[0];
        double d_i0 = D[1];

        double e_r0 = E[0];
        double e_i0 = E[1];

        _r00 += a_r0*d_r0 + a_i0*d_i0;
        _i00 += a_r0*d_i0 + a_i0*d_r0;

        _r01 += a_r0*e_r0 + a_i0*e_i0;
        _i01 += a_r0*e_i0 + a_i0*e_r0;

        _r10 += a_r1*d_r0 + a_i1*d_i0;
        _i10 += a_r1*d_i0 + a_i1*d_r0;

        _r11 += a_r1*e_r0 + a_i1*e_i0;
        _i11 += a_r1*e_i0 + a_i1*e_r0;

        a_r1 = A[4];
        a_i1 = A[5];

        b_r1 = B[4];
        b_i1 = B[5];

        d_r0 = D[2];
        d_i0 = D[3];

        e_r0 = E[2];
        e_i0 = E[3];

        _r20 += a_r1*d_r0 + a_i1*d_i0;
        _i20 += a_r1*d_i0 + a_i1*d_r0;

        _r21 += a_r1*e_r0 + a_i1*e_i0;
        _i21 += a_r1*e_i0 + a_i1*e_r0;

        k++;
        k_iter += 2;
        k_stop += 4;
        A += 4;
        B += 4;
        D += 2;
        E += 2;
    }

    sums[0] = _r00;
    sums[1] = _i00;
    sums[2] = _r01;
    sums[3] = _i01;
    sums[4] = _r10;
    sums[5] = _i10;
    sums[6] = _r11;
    sums[7] = _i11;
    sums[8] = _r20;
    sums[9] = _i20;
    sums[10] = _r21;
    sums[11] = _i21;
}