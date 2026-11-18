void Mat4_RotateQuaternion(float* dst, float* q) {
    float x = q[0], y = q[1], z = q[2], w = q[3];
    float x2 = x + x;
    float y2 = y + y;
    float z2 = z + z;

    float xx = x * x2;
    float xy = x * y2;
    float xz = x * z2;
    float yy = y * y2;
    float yz = y * z2;
    float zz = z * z2;
    float wx = w * x2;
    float wy = w * y2;
    float wz = w * z2;

    float out0x = dst[0] * (1 - yy - zz) + dst[1] * (xy - wz) + dst[2] * (xz + wy);
    float out0y = dst[0] * (xy + wz) + dst[1] * (1 - xx - zz) + dst[2] * (yz - wx);
    float out0z = dst[0] * (xz - wy) + dst[1] * (yz + wx) + dst[2] * (1 - xx - yy);

    float out1x = dst[4] * (1 - yy -zz) + dst[5] * (xy - wz) + dst[6] * (xz + wy);
    float out1y = dst[4] * (xy + wz) + dst[5] * (1 - xx - zz) + dst[6] * (yz - wx);
    float out1z = dst[4] * (xz - wy) + dst[5] * (yz + wx) + dst[6] * (1 - xx - yy);

    float out2x = dst[8] * (1 - yy -zz) + dst[9] * (xy - wz) + dst[10] * (xz + wy);
    float out2y = dst[8] * (xy + wz) + dst[9] * (1 - xx - zz) + dst[10] * (yz - wx);
    float out2z = dst[8] * (xz - wy) + dst[9] * (yz + wx) + dst[10] * (1 - xx - yy);

    dst[0] = out0x;
    dst[1] = out0y;
    dst[2] = out0z;
    dst[3] = dst[3];

    dst[4] = out1x;
    dst[5] = out1y;
    dst[6] = out1z;
    dst[7] = dst[7];

    dst[8] = out2x;
    dst[9] = out2y;
    dst[10] = out2z;
    dst[11] = dst[11];
}