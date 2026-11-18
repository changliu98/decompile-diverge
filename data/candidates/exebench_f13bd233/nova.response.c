void mtxLoadTranslate(float* t, float r, float g, float b) {
    t[0] = 1.0f;
    t[1] = 0.0f;
    t[2] = 0.0f;
    t[3] = 1.0f;
    t[4] = 0.0f;
    t[5] = 0.0f;
    t[6] = 0.0f;
    t[7] = 0.0f;
    t[8] = 0.0f;
    t[9] = 0.0f;
    t[10] = 1.0f;
    t[11] = 0.0f;
    t[12] = r;
    t[13] = g;
    t[14] = b;
    t[15] = 1.0f;
}