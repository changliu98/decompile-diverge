int func0(float x_coord, float y_coord, float z_coord)
{
    // Calculate squared terms for each variable
    double x_sq = (double)x_coord * x_coord;
    double y_sq = (double)y_coord * y_coord;
    double z_sq = (double)z_coord * z_coord;

    // Compute intermediate values: -c*c + a*a + b*b, -b*b + a*a + c*c, -a*a + b*b + c*c
    double sum_yz_minus_x = -z_sq + x_sq + y_sq;
    double sum_xz_minus_y = -y_sq + x_sq + z_sq;
    double sum_xy_minus_z = -x_sq + y_sq + z_sq;

    // Cast each value to unsigned long after double conversion, then apply bitwise AND with _DAT_00102010
    // Convert result back to double and compare with DAT_00102008
    int check_x = ((double)((ulong)(double)sum_yz_minus_x & _DAT_00102010) < DAT_00102008);
    int check_y = ((double)((ulong)(double)sum_xz_minus_y & _DAT_00102010) < DAT_00102008);
    int check_z = ((double)((ulong)(double)sum_xy_minus_z & _DAT_00102010) < DAT_00102008);

    // Return logical OR of all three conditions
    return check_x || check_y || check_z;
}