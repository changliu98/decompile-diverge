void invert_matrix(float *out, float *m)
{
    float a00, a01, a02, a03;
    float a10, a11, a12, a13;
    float a20, a21, a22, a23;
    float a30, a31, a32, a33;

    float b00, b01, b02, b03;
    float b04, b05, b06, b07;
    float b08, b09, b10, b11;
    float b12, b13, b14, b15;

    float det;

    a00 = m[0];
    a01 = m[1];
    a02 = m[2];
    a03 = m[3];
    a10 = m[4];
    a11 = m[5];
    a12 = m[6];
    a13 = m[7];
    a20 = m[8];
    a21 = m[9];
    a22 = m[10];
    a23 = m[11];
    a30 = m[12];
    a31 = m[13];
    a32 = m[14];
    a33 = m[15];


    b00 = a00 * a11 - a01 * a10;
    b01 = a00 * a12 - a02 * a10;
    b02 = a00 * a13 - a03 * a10;
    b03 = a01 * a12 - a02 * a11;
    b04 = a01 * a13 - a03 * a11;
    b05 = a02 * a13 - a03 * a12;
    b06 = a20 * a31 - a21 * a30;
    b07 = a20 * a32 - a22 * a30;
    b08 = a20 * a33 - a23 * a30;
    b09 = a21 * a32 - a22 * a31;
    b10 = a21 * a33 - a23 * a31;
    b11 = a22 * a33 - a23 * a32;


    b12 = a31 * b05 - a32 * b04 + a33 * b03;
    b13 = a32 * b02 - a30 * b05 - a33 * b01;
    b14 = a30 * b04 - a31 * b02 + a33 * b00;
    b15 = a31 * b01 - a30 * b03 - a32 * b00;


    det = b00 * b15 - b01 * b14 + b02 * b13 + b03 * b12 + b04 * b11 - b05 * b10;

    out[0] = (b11 * b05 - b12 * b04 + b13 * b03) / det;
    out[1] = (b12 * b02 - b10 * b05 - b13 * b01) / det;
    out[2] = (b10 * b04 - b11 * b02 + b13 * b00) / det;
    out[3] = (b11 * b01 - b10 * b03 - b12 * b00) / det;
    out[4] = (b09 * b04 - b08 * b05 - b07 * b03) / det;
    out[5] = (b08 * b05 - b09 * b02 + b07 * b01) / det;
    out[6] = (b09 * b00 - b08 * b01 - b07 * b00) / det;
    out[7] = (b09 * b03 - b08 * b01 - b09 * b00) / det;
    out[8] = (b06 * b05 - b07 * b04 + b08 * b03) / det;
    out[9] = (b07 * b02 - b06 * b05 - b08 * b01) / det;
    out[10] = (b06 * b04 - b07 * b02 + b08 * b00) / det;
    out[11] = (b07 * b01 - b06 * b03 - b08 * b00) / det;
    out[12] = (b06 * b05 - b07 * b04 - b08 * b03) / det;
    out[13] = (b07 * b02 - b06 * b05 + b08 * b01) / det;
    out[14] = (b06 * b04 - b07 * b02 - b08 * b00) / det;
    out[15] = (b07 * b03 - b06 * b01 - b08 * b00) / det;
}