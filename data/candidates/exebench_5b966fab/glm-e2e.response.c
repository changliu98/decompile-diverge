void load_inv(mat4 *out, const mat4 *in) {
    float s0 = in->m[0] * in->m[5] - in->m[4] * in->m[1];
    float s1 = in->m[0] * in->m[6] - in->m[4] * in->m[2];
    float s2 = in->m[0] * in->m[7] - in->m[4] * in->m[3];
    float s3 = in->m[1] * in->m[6] - in->m[5] * in->m[2];
    float s4 = in->m[1] * in->m[7] - in->m[5] * in->m[3];
    float s5 = in->m[2] * in->m[7] - in->m[6] * in->m[3];

    float c0 = in->m[8]  * in->m[13] - in->m[12] * in->m[9];
    float c1 = in->m[8]  * in->m[14] - in->m[12] * in->m[10];
    float c2 = in->m[8]  * in->m[15] - in->m[12] * in->m[11];
    float c3 = in->m[9]  * in->m[14] - in->m[13] * in->m[10];
    float c4 = in->m[9]  * in->m[15] - in->m[13] * in->m[11];
    float c5 = in->m[10] * in->m[15] - in->m[14] * in->m[11];

    float det = s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0;

    out->m[0]  = ( in->m[5] * c5 - in->m[6] * c4 + in->m[7] * c3) / det;
    out->m[1]  = (-in->m[1] * c5 + in->m[2] * c4 - in->m[3] * c3) / det;
    out->m[2]  = ( in->m[13] * s5 - in->m[14] * s4 + in->m[15] * s3) / det;
    out->m[3]  = (-in->m[9]  * s5 + in->m[10] * s4 - in->m[11] * s3) / det;

    out->m[4]  = (-in->m[4] * c5 + in->m[6] * c2 - in->m[7] * c1) / det;
    out->m[5]  = ( in->m[0] * c5 - in->m[2] * c2 + in->m[3] * c1) / det;
    out->m[6]  = (-in->m[12] * s5 + in->m[14] * s2 - in->m[15] * s1) / det;
    out->m[7]  = ( in->m[8]  * s5 - in->m[10] * s2 + in->m[11] * s1) / det;

    out->m[8]  = ( in->m[4] * c4 - in->m[5] * c2 + in->m[7] * c0) / det;
    out->m[9]  = (-in->m[0] * c4 + in->m[1] * c2 - in->m[3] * c0) / det;
    out->m[10] = ( in->m[12] * s4 - in->m[13] * s2 + in->m[15] * s0) / det;
    out->m[11] = (-in->m[8]  * s4 + in->m[9]  * s2 - in->m[11] * s0) / det;

    out->m[12] = (-in->m[4] * c3 + in->m[5] * c1 - in->m[6] * c0) / det;
    out->m[13] = ( in->m[0] * c3 - in->m[1] * c1 + in->m[2] * c0) / det;
    out->m[14] = (-in->m[12] * s3 + in->m[13] * s1 - in->m[14] * s0) / det;
    out->m[15] = ( in->m[8]  * s3 - in->m[9]  * s1 + in->m[10] * s0) / det;
}