void rmHSVtoRGB(float h, float s, float v, float *r, float *g, float *b)
{
    float f, p, q, t;
    float red, green, blue;
    int i;

    red = green = blue = 0.0;

    if (v == 0.0) {
        *r = red;
        *g = green;
        *b = blue;
        return;
    }

    if (s == 0.0) {
        red = green = blue = v;
        *r = red;
        *g = green;
        *b = blue;
        return;
    }

    h *= 60.0;
    i = (int)h;
    f = h - i;
    p = v * (1.0 - s);
    q = v * (1.0 - (s * f));
    t = v * (1.0 - (s * (1.0 - f)));

    switch (i) {
    case 0:
        red = v;
        green = t;
        blue = p;
        break;
    case 1:
        red = q;
        green = v;
        blue = p;
        break;
    case 2:
        red = p;
        green = v;
        blue = t;
        break;
    case 3:
        red = p;
        green = q;
        blue = v;
        break;
    case 4:
        red = t;
        green = p;
        blue = v;
        break;
    case 5:
        red = v;
        green = p;
        blue = q;
        break;
    }

    *r = red;
    *g = green;
    *b = blue;
}