void cquat_to_matrix_t(const double q[4], double m[9])
{







    double xx, xy, xz, xw, yy, yz, yw, zz, zw;

    xx = q[0] * q[0];
    xy = q[0] * q[1];
    xz = q[0] * q[2];
    xw = q[0] * q[3];

    yy = q[1] * q[1];
    yz = q[1] * q[2];
    yw = q[1] * q[3];

    zz = q[2] * q[2];
    zw = q[2] * q[3];

    m[0] = 1.0 - 2.0 * (yy + zz);
    m[1] = 2.0 * (xy + zw);
    m[2] = 2.0 * (xz - yw);

    m[3] = 2.0 * (xy - zw);
    m[4] = 1.0 - 2.0 * (zz + xx);
    m[5] = 2.0 * (yz + xw);

    m[6] = 2.0 * (xz + yw);
    m[7] = 2.0 * (yz - xw);
    m[8] = 1.0 - 2.0 * (xx + yy);
}