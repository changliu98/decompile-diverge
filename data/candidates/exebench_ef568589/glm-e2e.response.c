void mat3f_rotateQuatVec_new(float *out, float *q) {
    int i0 = 0;
    int i1 = 1;
    int i2 = 2;
    int i3 = 3;

    float dot = q[i0] * q[i0] + q[i1] * q[i1] + q[i2] * q[i2] + q[i3] * q[i3];
    float s = 2.0f / dot;

    float sx = s * q[i0];
    float sy = s * q[i1];
    float sz = s * q[i2];
    float sw = s * q[i3];

    float xx = q[i0] * sx;
    float xy = q[i0] * sy;
    float xz = q[i0] * sz;
    float yx = q[i1] * sx;
    float yy = q[i1] * sy;
    float yz = q[i1] * sz;
    float zz = q[i2] * sz;
    float wy = q[i1] * sw;
    float wz = q[i2] * sw;
    float wx = q[i0] * sw;

    out[0] = 1.0f - (yy + zz);
    out[3] = xy - wz;
    out[6] = xz + wy;
    out[1] = yx + wz;
    out[4] = 1.0f - (xx + zz);
    out[7] = yz - wx;
    out[2] = xz - wy;
    out[5] = yz + wx;
    out[8] = 1.0f - (xx + yy);
}