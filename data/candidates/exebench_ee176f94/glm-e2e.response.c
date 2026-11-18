int exactO(double x, double *out1, double *out2, double *out3, double *out4) {
    double t = 0.0; // Loaded from 0x2040

    // out2 = t * 0.5 + 1.0
    *out2 = t * 0.5 + 1.0;

    // out3 = (1.0 - *out2) * 2.0 / 3.0
    *out3 = (1.0 - *out2) * 2.0 / 3.0;

    // out4 = 0.5
    *out4 = 0.5;

    // out5 = (0.5 - *out3) / 0.5
    *out5 = (0.5 - *out3) / 0.5;

    if (x > 3.0) {
        *out1 = 1.0;
    } else if (x >= 0.0) {
        *out1 = *out2 + (1.0 - *out2) * (x / 3.0);
    } else {
        *out1 = *out2 + x * -1.0;
    }

    return 0;
}