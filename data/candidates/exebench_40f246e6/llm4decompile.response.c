float interp_tri(float z[4], float x, float y, int grid_scheme)
{
    double z0, z1, z2, z3;
    double xx, yy;
    double a, b, c, d, e, f;

    xx = (((x) < (0.000001)) ? (0.000001) : (((x) > (0.999999)) ? (0.999999) : (x)));
    yy = (((y) < (0.000001)) ? (0.000001) : (((y) > (0.999999)) ? (0.999999) : (y)));

    if (xx == 0.0)
    {
        if (yy == 0.0)
            return z[0];
        if (yy == 0.999999)
            return z[2];
    }
    if (xx == 0.999999)
    {
        if (yy == 0.0)
            return z[1];
        if (yy == 0.999999)
            return z[3];
    }

    if (grid_scheme > 0)
    {
        z0 = z[0];
        z1 = z[1];
        z2 = z[3];
        z3 = z[2];
    }
    else
    {
        z0 = z[0];
        z1 = z[1];
        z2 = z[2];
        z3 = z[3];
        xx = 0.999999 - xx;
    }

    if (xx < yy)
    {
        a = z0;
        b = z1;
        c = z2;
        d = z3;
        e = 0.999999 - xx;
        f = 0.999999 - yy;
    }
    else
    {
        a = z0;
        b = z2;
        c = z3;
        d = z1;
        e = yy;
        f = xx;
    }

    return (float)(((a * e + b * f - c * e) * (e / f) + c * f));
}