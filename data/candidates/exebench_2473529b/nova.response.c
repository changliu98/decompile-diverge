void normalize_angle(double *x) {
    if (*x > MAX)
        *x = MAX;
    else {
        if (*x < MIN)
            *x = MIN;
    }
}