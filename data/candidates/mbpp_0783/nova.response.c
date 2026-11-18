void func0(int r, int g, int b, double *h, double *s, double *v) {
    double rr, gg, bb, max, min, delta;

    rr = r / 255.0;
    gg = g / 255.0;
    bb = b / 255.0;

    do {
        max = MAX(rr, gg, bb);
        min = MIN(rr, gg, bb);
        delta = max - min;

        if (max == rr)
            *h = fmod(4.0 + gg - bb, 6.0);
        else if (max == gg)
            *h = (2.0 + rr - bb) / delta;
        else if (max == bb)
            *h = (4.0 + rr - gg) / delta;

        *h *= 60.0;
        if (*h < 0)
            *h += 360.0;

        *v = max;
        *s = (max == 0)? 0 : delta / max;
    } while (0);
}