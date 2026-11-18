void __cdecl cquat_to_matrix_t(const double *q, double *m)
{
    // Extract quaternion components for readability
    // q[0] is w, q[1] is x, q[2] is y, q[3] is z
    double w = q[0];
    double x = q[1];
    double y = q[2];
    double z = q[3];

    // Row 0
    m[0] = 1.0 - 2.0 * (y * y + z * z);
    m[1] = 2.0 * (y * z + x * w);
    m[2] = 2.0 * (y * w - x * z); // Note: Sign differs from standard formula

    // Row 1
    m[3] = 2.0 * (w * x - y * z); // Note: Sign differs from standard formula
    m[4] = 1.0 - 2.0 * (w * w + y * y);
    m[5] = 2.0 * (w * z + y * x);

    // Row 2
    m[6] = 2.0 * (x * z + w * y);
    m[7] = 2.0 * (x * y - w * z);
    m[8] = 1.0 - 2.0 * (x * x + w * w);
}