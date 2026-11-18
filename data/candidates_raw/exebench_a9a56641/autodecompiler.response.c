void mat4_mul(float* dst, float* b, float* a) {
    float a00 = a[0], a01 = a[1], a02 = a[2], a03 = a[3];
    float a10 = a[4], a11 = a[5], a12 = a[6], a13 = a[7];
    float a20 = a[8], a21 = a[9], a22 = a[10], a23 = a[11];
    float a30 = a[12], a31 = a[13], a32 = a[14], a33 = a[15];


    float b00 = b[0], b01 = b[1], b02 = b[2], b03 = b[3];
    float b10 = b[4], b11 = b[5], b12 = b[6], b13 = b[7];
    float b20 = b[8], b21 = b[9], b22 = b[10], b23 = b[11];
    float b30 = b[12], b31 = b[13], b32 = b[14], b33 = b[15];

    float c00 = b00 * a00 + b01 * a10 + b02 * a20 + b03 * a30;
    float c01 = b00 * a01 + b01 * a11 + b02 * a21 + b03 * a31;
    float c02 = b00 * a02 + b01 * a12 + b02 * a22 + b03 * a32;
    float c03 = b00 * a03 + b01 * a13 + b02 * a23 + b03 * a33;

    float c10 = b10 * a00 + b11 * a10 + b12 * a20 + b13 * a30;
    float c11 = b10 * a01 + b11 * a11 + b12 * a21 + b13 * a31;
    float c12 = b10 * a02 + b11 * a12 + b12 * a22 + b13 * a32;
    float c13 = b10 * a03 + b11 * a13 + b12 * a23 + b13 * a33;

    float c20 = b20 * a00 + b21 * a10 + b22 * a20 + b23 * a30;
    float c21 = b20 * a01 + b21 * a11 + b22 * a21 + b23 * a31;
    float c22 = b20 * a02 + b21 * a12 + b22 * a22 + b23 * a32;
    float c23 = b20 * a03 + b21 * a13 + b22 * a23 + b23 * a33;

    float c30 = b30 * a00 + b31 * a10 + b32 * a20 + b33 * a30;
    float c31 = b30 * a01 + b31 * a11 + b32 * a21 + b33 * a31;
    float c32 = b30 * a02 + b31 * a12 + b32 * a22 + b33 * a32;
    float c33 = b30 * a03 + b31 * a13 + b32 * a23 + b33 * a33;

    dst[0] = c00;
    dst[1] = c01;
    dst[2] = c02;
    dst[3] = c03;
    dst[4] = c10;
    dst[5] = c11;
    dst[6] = c12;
    dst[7] = c13;
    dst[8] = c20;
    dst[9] = c21;
    dst[10] = c22;
    dst[11] = c23;
    dst[12] = c30;
    dst[13] = c31;
    dst[14] = c32;
    dst[15] = c33;
}