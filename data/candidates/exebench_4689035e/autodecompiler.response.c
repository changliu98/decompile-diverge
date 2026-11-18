void rgb2hsv(double r, double g, double b, double *h, double *s, double *v)
{
    double min, max, delta, rc, gc, bc;

    double hue = 0;
    double saturation = 0;
    double value = 0;

    min = ((r < g) ? r : g);
    min = ((min < b) ? min : b);

    max = ((r > g) ? r : g);
    max = ((max > b) ? max : b);

    value = max;
    delta = max - min;

    if (value != 0.0)
        saturation = delta / value;

    if (saturation != 0.0) {
        rc = (max - r) / delta;
        gc = (max - g) / delta;
        bc = (max - b) / delta;

        if (r == max)
            hue = bc - gc;
        else if (g == max)
            hue = 2 + rc - bc;
        else if (b == max)
            hue = 4 + gc - rc;

        hue *= 60.0;
        if (hue < 0.0)
            hue += 360.0;
    }

    *h = hue / 360.0;
    *v = value;
    *s = saturation;
}