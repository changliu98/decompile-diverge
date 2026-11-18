void func0(int r, int g, int b, double *h, double *s, double *v)
{
    double rd, gd, bd;
    double mx, mn;
    double df;

    rd = (double)r / 255.0;
    gd = (double)g / 255.0;
    bd = (double)b / 255.0;

    mx = (((rd) > (gd) ? (rd) : (gd))) > (bd) ? (((rd) > (gd) ? (rd) : (gd))) : (bd));
    mn = (((rd) < (gd) ? (rd) : (gd))) < (bd) ? (((rd) < (gd) ? (rd) : (gd))) : (bd));

    *h = 0.0;
    df = mx - mn;
    if (df > 0.0) {
        if (mx == rd) {
            *h = fmod((gd - bd) / df * 60.0 + 360.0, 360.0);
        } else if (mx == gd) {
            *h = fmod((bd - rd) / df * 60.0 + 120.0, 360.0);
        } else if (mx == bd) {
            *h = fmod((rd - gd) / df * 60.0 + 240.0, 360.0);
        }
    }

    if (mx == 0.0) {
        *s = 0.0;
    } else {
        *s = (df / mx) * 100.0;
    }

    *v = mx * 100.0;

    return;
}