void qtomat(float *q, float *m) {
    float w = q[0];
    float x = q[1];
    float y = q[2];
    float z = q[3];

    // Row 0
    m[0] = w * w + x * x - y * y - z * z;
    m[1] = 2.0f * (x * y - w * z);
    m[2] = 2.0f * (x * z + w * y);

    // Row 1
    m[3] = 2.0f * (x * y + w * z);
    m[4] = w * w - x * x + y * y - z * z;
    m[5] = 2.0f * (y * z - w * x);

    // Row 2
    m[6] = 2.0f * (x * z - w * y);
    m[7] = 2.0f * (y * z + w * x);
    m[8] = w * w - x * x - y * y + z * z;
}