void
mat3d_rotateQuatVec_new(double matrix[3][3],
                        const double quat[4])
{
    double Nq = quat[0]*quat[0] + quat[1]*quat[1] + quat[2]*quat[2] + quat[3]*quat[3];
    double s = 2.0/Nq;

    double xs = quat[0] * s, ys = quat[1] * s, zs = quat[2] * s;
    double wx = quat[3] * xs, wy = quat[3] * ys, wz = quat[3] * zs;
    double xx = quat[0] * xs, xy = quat[0] * ys, xz = quat[0] * zs;
    double yy = quat[1] * ys, yz = quat[1] * zs, zz = quat[2] * zs;
    double wyz = wy + xz, wxz = wz + xy;

    matrix[0][0] = 1.0 - (yy + zz);
    matrix[1][0] = xy - wz;
    matrix[2][0] = xz + wy;

    matrix[0][1] = xy + wz;
    matrix[1][1] = 1.0 - (xx + zz);
    matrix[2][1] = yz - wx;

    matrix[0][2] = xz - wy;
    matrix[1][2] = yz + wx;
    matrix[2][2] = 1.0 - (xx + yy);
}