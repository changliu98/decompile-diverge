void rmHSVtoRGB(float h, float s, float v, float *r, float *g, float *b) {
    float fR = 0.0f, fG = 0.0f, fB = 0.0f;
    float hh = h;
    
    // If saturation is 0, the color is a shade of gray
    if (v == 0.0f) {
        *r = 0.0f;
        *g = 0.0f;
        *b = 0.0f;
        return;
    } 
    
    // If value is 0, the color is black
    if (s == 0.0f) {
        *r = v;
        *g = v;
        *b = v;
        return;
    }
    
    // Normalize hue to be between 0 and 6
    hh = hh * 6.0f;
    if (hh >= 6.0f) {
        hh = 0.0f;
    }
    
    int i = (int)hh;
    float f = hh - i;
    float p = v * (1.0f - s);
    float q = v * (1.0f - s * f);
    float t = v * (1.0f - s * (1.0f - f));
    
    // Assign RGB values based on the hue sector
    switch (i) {
        case 0:
            fR = v;
            fG = t;
            fB = p;
            break;
        case 1:
            fR = q;
            fG = v;
            fB = p;
            break;
        case 2:
            fR = p;
            fG = v;
            fB = t;
            break;
        case 3:
            fR = p;
            fG = q;
            fB = v;
            break;
        case 4:
            fR = t;
            fG = p;
            fB = v;
            break;
        case 5:
            fR = v;
            fG = p;
            fB = q;
            break;
    }
    
    *r = fR;
    *g = fG;
    *b = fB;
}