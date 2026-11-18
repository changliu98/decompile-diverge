void xformSetTranslation(float* t, float r, float s) {
    t[0] = 1.0f;
    t[1] = 0.0f;
    t[2] = 0.0f;
    t[3] = 1.0f;
    t[4] = r;
    t[5] = s;
}