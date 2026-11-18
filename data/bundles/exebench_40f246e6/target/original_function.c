float interp_tri (float *z, float x, float y, int grid_scheme)

{

    register double xx, yy, z0, z1, z2, z3, za, zb, zc;


    xx = (x < 1.0e-05) ? 0.0 : (x > (1.0 - 1.0e-05)) ? 1.0 : x;
    yy = (y < 1.0e-05) ? 0.0 : (y > (1.0 - 1.0e-05)) ? 1.0 : y;

    if (xx == 0.0)
    {
        if (yy == 0.0) return z[0];
        if (yy == 1.0) return z[2];
    }
    else if (xx == 1.0)
    {
        if (yy == 0.0) return z[1];
        if (yy == 1.0) return z[3];
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
        xx = 1.0 - xx;
        z0 = z[1];
        z1 = z[0];
        z2 = z[2];
        z3 = z[3];
    }

    if (yy <= xx)
        za = z0, zb = z1, zc = z2;
    else
        za = z2, zb = z3, zc = z0, xx = 1.0 - xx, yy = 1.0 - yy;

    z0 = za + ((zb - za) * xx);
    z1 = za + ((zc - za) * xx);


    return z0 + ((z1 - z0) * (yy / xx));
}