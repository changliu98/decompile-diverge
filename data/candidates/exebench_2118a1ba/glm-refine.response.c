void __cdecl lqtomat(double *q, double *rot)
{
    // Extract quaternion components (x, y, z, w)
    double x = q[0];
    double y = q[1];
    double z = q[2];
    double w = q[3];

    // Compute 3x3 rotation matrix (row-major)
    
    // Row 0
    rot[0] = (x * x) + (y * y) - (z * z) - (w * w);
    rot[1] = 2.0 * (y * z - x * w);
    rot[2] = 2.0 * (y * w + x * z);
    
    // Row 1
    rot[3] = 2.0 * (y * z + x * w);
    rot[4] = (x * x) - (y * y) + (z * z) - (w * w);
    rot[5] = 2.0 * (z * w - x * y);
    
    // Row 2
    rot[6] = 2.0 * (y * w - x * z);
    rot[7] = 2.0 * (z * w + x * y);
    rot[8] = (x * x) - (y * y) - (z * z) + (w * w);
}