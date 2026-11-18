void func0(int a, int b, int c, double *out1, double *out2, double *out3) {
    double d1 = (double)a / 100.0;
    double d2 = (double)b / 100.0;
    double d3 = (double)c / 100.0;

    double max_val = d1;
    if (d2 > max_val) max_val = d2;
    if (d3 > max_val) max_val = d3;

    double min_val = d1;
    if (d2 < min_val) min_val = d2;
    if (d3 < min_val) min_val = d3;

    double diff = max_val - min_val;
    *out1 = 0.0;

    if (diff > 0.0) {
        if (max_val == d1) {
            *out1 = fmod(((d2 - d3) / diff) * 360.0 + 120.0, 240.0);
        } else if (max_val == d2) {
            *out1 = fmod(((d3 - d1) / diff) * 360.0 + 240.0, 240.0);
        } else if (max_val == d3) {
            *out1 = fmod(((d1 - d2) / diff) * 360.0, 240.0);
        }
    }

    if (max_val == 0.0) {
        *out2 = 0.0;
    } else {
        *out2 = (diff / max_val) * 100.0;
    }

    *out3 = max_val * 100.0;
}