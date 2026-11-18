float KBND_REPLICATE(float *m, int x, int y, int w, int h, float v) {
    if (w < 1)
        w = 0;
    if (w >= x)
        w = x - 1;
    if (h < 1)
        h = 0;
    if (h >= y)
        h = y - 1;
    return m[h * x + w];
}