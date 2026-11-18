int func0(int hh, int mm, float ss, double *d) {
    int rc;

    *d = hh + (mm / 60.0) + (ss / 3600.0);
    *d *= 360.0 / 24.0;

    if (*d > 180.0)
        rc = 1;
    else if (*d < -180.0)
        rc = 1;
    else
        rc = 0;

    return rc;
}