static void func0(const double *m, double *det) {
    *det = m[0] * (m[4] * m[8] - m[7] * m[5]) -
           m[1] * (m[3] * m[8] - m[6] * m[5]) +
           m[2] * (m[3] * m[7] - m[6] * m[4]);
}