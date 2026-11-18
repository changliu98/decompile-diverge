void drwav_f64_to_s32(double *out, const double *in, const size_t len) {
    size_t i;

    if (!out ||!in) {
        return;
    }

    for (i = 0; i < len; i++) {
        out[i] = (int)(in[i] * (double)180.0 / M_PI);
    }
}