void innerdct(const double *in, double *out, const double *basis) {
    // Butterfly stage: compute sums and differences
    double s0 = in[0] + in[7];
    double s1 = in[1] + in[6];
    double s2 = in[2] + in[5];
    double s3 = in[3] + in[4];

    double d0 = in[0] - in[7];
    double d1 = in[1] - in[6];
    double d2 = in[2] - in[5];
    double d3 = in[3] - in[4];

    // Even terms (0, 2, 4, 6)
    double e0 = (s0 + s3) * basis[4];
    double e1 = (s1 + s2) * basis[4];
    out[0] = e0 + e1;
    out[32] = e0 - e1;

    out[16] = (s0 - s3) * basis[2] + (s1 - s2) * basis[6];
    out[48] = (s0 - s3) * basis[6] - (s1 - s2) * basis[2];

    // Odd terms (1, 3, 5, 7)
    out[8]  = d0 * basis[1] + d1 * basis[3] + d2 * basis[5] + d3 * basis[7];
    out[24] = d0 * basis[3] - d1 * basis[7] - d2 * basis[1] - d3 * basis[5];
    out[40] = d0 * basis[5] - d1 * basis[1] + d2 * basis[7] + d3 * basis[3];
    out[56] = d0 * basis[7] - d1 * basis[5] + d2 * basis[3] - d3 * basis[1];
}