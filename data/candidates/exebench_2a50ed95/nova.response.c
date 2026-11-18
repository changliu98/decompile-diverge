void ZVdotC21(int n, double *a, double *b, double *c, double *d, double *e) {
    int i, j, k;
    double sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;

    for (i = 0, j = 1, k = 2; i < n; i++, j += 2, k += 2) {
        double a_ik = a[i * n + k], a_kj = a[k * n + j], b_ik = b[i * n + k],
               b_kj = b[k * n + j], c_ik = c[i * n + k], c_kj = c[k * n + j],
               d_ik = d[i * n + k], d_kj = d[k * n + j];

        sum1 += a_ik * b_kj + a_kj * b_ik;
        sum2 += b_ik * c_kj + b_kj * c_ik;
        sum3 += c_ik * d_kj + c_kj * d_ik;
        sum4 += d_ik * a_kj + d_kj * a_ik;
    }

    e[0] = sum1;
    e[1] = sum2;
    e[2] = sum3;
    e[3] = sum4;
}