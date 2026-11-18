void mat3_transpose(float* dst) {
    float a01 = dst[1], a02 = dst[2], a10 = dst[4], a12 = dst[5], a20 = dst[8], a21 = dst[9];
    dst[1] = a01; dst[2] = a02; dst[4] = a10; dst[5] = a12; dst[8] = a20; dst[9] = a21;

    float t;
    t = dst[6];
    dst[6] = dst[7];
    dst[7] = t;

    t = dst[11];
    dst[11] = dst[14];
    dst[14] = t;

    t = dst[12];
    dst[12] = dst[13];
    dst[13] = t;

    t = dst[15];
    dst[15] = dst[19];
    dst[19] = t;

    t = dst[17];
    dst[17] = dst[18];
    dst[18] = t;

    t = dst[16];
    dst[16] = dst[22];
    dst[22] = t;
}