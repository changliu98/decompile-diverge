void __cdecl rgb2hsv(int r, int g, int b, int *h, int *s, int *v)
{
    // Find the maximum component
    int max = (r > g) ? r : g;
    if (b > max)
        max = b;

    // Find the minimum component
    int min = (r < g) ? r : g;
    if (b < min)
        min = b;

    // Calculate delta (max - min)
    int delta = max - min;

    if (max == 0)
    {
        // Black pixel: value is 0, hue and saturation are undefined/0
        *v = 0;
        *h = 0;
        *s = 0;
        return;
    }

    // Calculate Hue (scaled by 10, so 0 to 3600)
    if (delta == 0)
    {
        *h = 0;
    }
    else if (max == r)
    {
        // Red is max
        *h = 600 * (g - b) / delta;
        if (g < b)
            *h += 3600;
    }
    else if (max == g)
    {
        // Green is max
        *h = 10 * (60 * (b - r) / delta + 120);
    }
    else
    {
        // Blue is max
        *h = 10 * (60 * (r - g) / delta + 240);
    }

    // Normalize Hue to the range [0, 3600)
    while (*h < 0)
        *h += 3600;
    while (*h >= 3600)
        *h -= 3600;

    // Calculate Saturation and Value
    *s = 255 * delta / max;
    *v = max;
}