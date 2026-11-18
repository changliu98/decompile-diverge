void func0(int r, int g, int b, double *h, double *s, double *v)
{
    double min, max, delta, rc, gc, bc;

    rc = ((double) r / 255.0);
    gc = ((double) g / 255.0);
    bc = ((double) b / 255.0);

    max = (((rc) > ((((gc) > (bc)) ? (gc) : (bc)))) ? (rc) : ((((gc) > (bc)) ? (gc) : (bc))));
    min = (((rc) < ((((gc) < (bc)) ? (gc) : (bc)))) ? (rc) : ((((gc) < (bc)) ? (gc) : (bc))));
    delta = max - min;

    *h = 0;
    if (delta > 0.0) {
        if (max == rc) {
            *h = fmod((gc - bc) / delta + 360.0, 360.0);
        } else if (max == gc) {
            *h = fmod((bc - rc) / delta + 120.0, 360.0);
        } else if (max == bc) {
            *h = fmod((rc - gc) / delta + 240.0, 360.0);
        }
    }

    if (max == 0.0) {
        *s = 0.0;
    } else {
        *s = (delta / max) * 100.0;
    }

    *v = max * 100.0;
}