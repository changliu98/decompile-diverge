void ne_pre_filter8_double(struct Output *out, struct Coeffs *c, struct State *st) {
    // 1. Calculate intermediate differences (d0 to d3)
    double d0 = c->x[0] - c->y[7];
    double d1 = c->x[1] - c->y[6];
    double d2 = c->x[2] - c->y[5];
    double d3 = c->x[3] - c->y[4];

    // 2. Update state variables (s0 to s3)
    double s0 = c->x[3] - (d3 / 2.0);
    double s1 = c->x[2] - (d2 / 2.0);
    double s2 = c->x[1] - (d1 / 2.0);
    double s3 = c->x[0] - (d0 / 2.0);

    // 3. Scale state variables by coefficients (c->x[4] to c->x[7])
    d3 = (d3 * (double)st->s[0]) / 6.0;
    d2 = (d2 * (double)st->s[1]) / 6.0;
    d1 = (d1 * (double)st->s[2]) / 6.0;
    d0 = (d0 * (double)st->s[3]) / 6.0;

    // 4. Accumulate terms into state variables
    d0 += (d1 * (double)st->s[6]) / 6.0;
    d1 += (d0 * (double)st->s[9]) / 6.0;
    d1 += (d2 * (double)st->s[5]) / 6.0;
    d2 += (d1 * (double)st->s[8]) / 6.0;
    d2 += (d3 * (double)st->s[4]) / 6.0;
    d3 += (d2 * (double)st->s[7]) / 6.0;

    // 5. Finalize outputs (out[0] to out[3])
    out->out[0] = s3 + (d0 / 2.0);
    out->out[1] = s2 + (d1 / 2.0);
    out->out[2] = s1 + (d2 / 2.0);
    out->out[3] = s0 + (d3 / 2.0);

    // 6. Calculate outputs (out[4] to out[7])
    out->out[4] = out->out[3] - d3;
    out->out[5] = out->out[2] - d2;
    out->out[6] = out->out[1] - d1;
    out->out[7] = out->out[0] - d0;
}