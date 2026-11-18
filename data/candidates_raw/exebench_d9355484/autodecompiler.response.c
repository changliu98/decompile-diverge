void rgb_to_hsv(float r, float g, float b, float *h, float *s, float *v)
{
    float min = ((r < g) ? ((r < b) ? r : b) : ((g < b) ? g : b));
    float max = ((r > g) ? ((r > b) ? r : b) : ((g > b) ? g : b));
    float delta = max - min;

    *v = max;
    if (max != 0.0f)
        *s = delta / max;
    else {
        *s = 0.0f;
        *h = -1.0f;
        return;
    }

    if (r == max)
        *h = (g - b) / delta;
    else if (g == max)
        *h = 2 + (b - r) / delta;
    else
        *h = 4 + (r - g) / delta;
    *h *= 60.0f;
    if (*h < 0.0f)
        *h += 360.0f;
}