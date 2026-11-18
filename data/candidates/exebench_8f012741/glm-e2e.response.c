void lin_solve_2(double *out, const double *m, const double *b) {
    double det = m[0] * m[3] - m[1] * m[2];
    double inv_det = 1.0 / det;
    
    out[0] = inv_det * (m[3] * b[0] - m[1] * b[1]);
    out[1] = inv_det * (m[0] * b[1] - m[2] * b[0]);
}