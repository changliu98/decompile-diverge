int __cdecl ctr_intersect(double z0, double z1, double zc, double *f)
{
    // Check if zc is strictly between z0 and z1.
    // The product of (z0 - zc) and (z1 - zc) is negative if and only if 
    // zc lies strictly inside the open interval (min(z0, z1), max(z0, z1)).
    if ((z0 - zc) * (z1 - zc) >= 0.0)
        return 0;

    // Calculate the linear interpolation factor.
    // This represents how far along the line from z0 to z1 the intersection occurs.
    if (f)
        *f = (zc - z0) / (z1 - z0);

    return 1;
}