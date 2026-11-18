void mat3d_rotateQuatVec_new(double out[3][4], const double q[4]) {
    int i0 = 0;
    int i1 = 1;
    int i2 = 2;
    int i3 = 3;

    double n2 = q[i0] * q[i0] + q[i1] * q[i1] + q[i2] * q[i2] + q[i3] * q[i3];
    double s = 2.0 / n2;

    double xs = q[i0] * s;
    double ys = q[i1] * s;
    double zs = q[i2] * s;

    double wx = q[i3] * xs;
    double wy = q[i3] * ys;
    double wz = q[i3] * zs;

    double xx = q[i0] * xs;
    double xy = q[i0] * ys;
    double xz = q[i0] * zs;

    double yy = q[i1] * ys;
    double yz = q[i1] * zs;
    double zz = q[i2] * zs;

    out[0][0] = 1.0 - (yy + zz);
    out[0][1] = xy - wz;
    out[0][2] = xz + wy;
    
    out[1][0] = xy + wz;
    out[1][1] = 1.0 - (xx + zz);
    out[1][2] = yz - wx;
    
    out[2][0] = xz - wy;
    out[2][1] = yz + wx;
    out[2][2] = 1.0 - (xx + yy);
}