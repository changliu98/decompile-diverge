void mat4f_LoadScale(const float *v, float *m) {
    m[0]  = v[0];
    m[1]  = 0.0f;
    m[2]  = 0.0f;
    m[3]  = 0.0f;

    m[4]  = 0.0f;
    m[5]  = v[1];
    m[6]  = 0.0f;
    m[7]  = 0.0f;

    m[8]  = 0.0f;
    m[9]  = 0.0f;
    m[10] = v[2];
    m[11] = 0.0f;

    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f; // Loaded from a constant in memory (at RIP+0xd48)
}