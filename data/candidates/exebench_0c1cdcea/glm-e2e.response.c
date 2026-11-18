void TriggsM(const double *in, double *out) {
    double a = in[0];
    double b = in[1];
    double c = in[2];

    double t0 = (1.0 + c - b + a) * (1.0 - c - b - a) * (b - a * (c - a * a)) ;
    double t1 = 1.0 / t0;

    out[0] = t1 * (-a * c + 1.0 - a * a - b);
    out[1] = t1 * (a + c) * (b + a * c);
    out[2] = t1 * a * (c + a * b);
    out[3] = t1 * (c + a * b);
    out[4] = -t1 * (b - 1.0) * (b + a * c);
    out[5] = -t1 * a * (a * c + a * a + b - 1.0);
    out[6] = t1 * (b + a * c + c * c - b * b) * (b - a * c);
    out[7] = t1 * (b * b - b * c - a * c * c - a * a * a - a * b + a) * (c + a * b);
    out[8] = t1 * a * (c + a * b);
}