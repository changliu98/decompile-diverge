int shape_tria3(const double *in, double *out) {
    out[0] = in[0];
    out[1] = in[1];
    out[2] = 1.0 - in[0] - in[1];
    return 0;
}