void ne_pre_filter8_double(double *out, const double *in, const int *size) {
    double x = in[0] - size[0];
    double y = in[1] - size[1];
    double z = in[2] - size[2];
    double w = in[3] - size[3];
    double h = in[3] - size[3];
    double v = in[4] - size[4];

    x = x * size[6] / 1000.0;
    y = y * size[7] / 1000.0;
    z = z * size[8] / 1000.0;
    w = w * size[9] / 1000.0;
    h = h * size[10] / 1000.0;
    v = v * size[11] / 1000.0;

    out[0] = x;
    out[1] = y;
    out[2] = z;
    out[3] = w;
    out[4] = h;
    out[5] = v;
}