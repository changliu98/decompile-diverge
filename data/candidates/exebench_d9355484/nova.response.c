void RGBtoHSV(float x, float y, float z, float *h, float *s, float *v) {
    float r, g, b, max, min, delta;
    r = x;
    g = y;
    b = z;
    if (y > z)
        max = y;
    else
        max = z;
    if (r > max)
        min = max;
    else
        min = z;
    delta = max - min;
    *v = max;
    if (max!= 0)
        *s = delta / max;
    else
        *s = 0;
    if (max == r)
        *h = (g - b) / delta;
    if (max == g)
        *h = (b - r) / delta + 2;
    if (max == b)
        *h = (r - g) / delta + 4;
    *h *= 60;
    if (*h < 0)
        *h += 360;
}