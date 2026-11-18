void mat3f_rotateQuatVec_new(float* matrix, const float* quat)
{
    float xx, xy, xz, xw, yy, yz, yw, zz, zw;
    float s;

    s = 2.0 / (quat[0]*quat[0] + quat[1]*quat[1] + quat[2]*quat[2] + quat[3]*quat[3]);

    xx = quat[0] * quat[0] * s;
    xy = quat[0] * quat[1] * s;
    xz = quat[0] * quat[2] * s;
    xw = quat[0] * quat[3] * s;
    yy = quat[1] * quat[1] * s;
    yz = quat[1] * quat[2] * s;
    yw = quat[1] * quat[3] * s;
    zz = quat[2] * quat[2] * s;
    zw = quat[2] * quat[3] * s;

    matrix[0] = 1.0 - (yy + zz);
    matrix[1] = xy - zw;
    matrix[2] = xz + yw;

    matrix[3] = xy + zw;
    matrix[4] = 1.0 - (zz + xx);
    matrix[5] = yz - xw;

    matrix[6] = xz - yw;
    matrix[7] = yz + xw;
    matrix[8] = 1.0 - (xx + yy);
}