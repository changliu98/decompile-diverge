float __cdecl interp_tri(float *z, float x, float y, int grid_scheme)
{
    // Clamp x and y between 0.0 and 1.0
    double xx = fmax(0.0, fmin(1.0, (double)x));
    double yy = fmax(0.0, fmin(1.0, (double)y));

    // Return exact corner values if applicable
    if (xx == 0.0)
    {
        if (yy == 0.0) return *z;
        if (yy == 1.0) return z[2];
    }
    else if (xx == 1.0)
    {
        if (yy == 0.0) return z[1];
        if (yy == 1.0) return z[3];
    }

    double z0;
    struct vec2 z2;
    double z3;

    // Select grid orientation
    if (grid_scheme <= 0)
    {
        xx = 1.0 - xx;
        z0 = z[1];
        z2.y = *z;
        z2.x = z[2];
        z3 = z[3];
    }
    else
    {
        z0 = *z;
        z2.y = z[1];
        z2.x = z[3];
        z3 = z[2];
    }

    double za;
    struct vec2 zc;

    // Select triangle for interpolation
    if (xx < yy)
    {
        za = z2.x;
        zc.y = z3;
        zc.x = z0;
        xx = 1.0 - xx;
        yy = 1.0 - yy;
    }
    else
    {
        za = z0;
        zc = z2;
    }

    // Barycentric interpolation
    double term1 = (zc.x - za) * xx;
    double term2 = (zc.y - za) * xx;
    
    return (float)((term1 - term2) * (yy / xx) + term2 + za);
}