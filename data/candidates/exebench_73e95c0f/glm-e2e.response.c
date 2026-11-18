void clamp(double *val, double max, double min) {
    if (*val > max) {
        *val = max;
    } else if (*val < min) {
        *val = min;
    }
}