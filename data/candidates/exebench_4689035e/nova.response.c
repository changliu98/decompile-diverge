void rgb2hsv(double a, double b, double c, double *x1, double *x2,
               double *delta) {
    double x, y, z;
    double d;

    do {
        d = d * -1.0;
        x = a;
        y = b;
        z = c;

        if (x > y) {
            x = x + y;
            y = x - y;
            x = x - y;
        }

        if (x > z) {
            x = x + z;
            z = x - z;
            x = x - z;
        }

        if (y > z) {
            y = y + z;
            z = y - z;
            y = y - z;
        }

        d = y - x;
        d = d / (x - z);

        y = y - d;
        z = z - d;

        if (x == y) {
            y = y + (1.0 / 3.0);
            z = z + (1.0 / 3.0);
        }

        if (y == z) {
            y = y + (1.0 / 3.0);
            z = z + (1.0 / 3.0);
        }

        *delta = d / 3.0;
        *x1 = x;
        *x2 = y;
    } while (d < 0);
}