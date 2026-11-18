void mtxScaleMatrix(float *m, float x, float y, float z) {
    // Scale the first column (X axis)
    m[0]  *= x;
    m[4]  *= x;
    m[8]  *= x;
    m[12] *= x;

    // Scale the second column (Y axis)
    m[1]  *= y;
    m[5]  *= y;
    m[9]  *= y;
    m[13] *= y;

    // Scale the third column (Z axis)
    m[2]  *= z;
    m[6]  *= z;
    m[10] *= z;
    m[14] *= z;
}