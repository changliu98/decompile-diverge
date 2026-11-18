void __cdecl rgb_2_hls(int r, int g, int b, int *h, int *l, int *s)
{
    int min, max, t;

    // Calculate the minimum of the three RGB components
    min = (g < r) ? g : r;
    if (min > b)
        min = b;

    // Calculate the maximum of the three RGB components
    max = (g > r) ? g : r;
    if (max < b)
        max = b;

    // Calculate Lightness (L) scaled to 0-100
    *l = (max + min) / 20;

    if (min == max)
    {
        // Achromatic case (grayscale)
        *h = 0;
        *s = 0;
    }
    else
    {
        // Calculate Saturation (S) scaled to 0-100
        if (*l >= 50)
            *s = 100 * (max - min) / (2000 - max - min);
        else
            *s = 100 * (max - min) / (min + max);

        // Calculate Hue (H) scaled to 0-359 degrees
        if (r == max)
        {
            t = 60 * (g - b) / (max - min) + 120;
        }
        else if (g == max)
        {
            t = 60 * (b - r) / (max - min) + 240;
        }
        else // b == max
        {
            t = 60 * (r - g) / (max - min) + 360;
        }
        
        // Wrap around the hue circle
        *h = t % 360;
    }
}