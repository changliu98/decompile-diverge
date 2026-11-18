void rgb2hsv(int r, int g, int b, int *h, int *s, int *v) {
    int max = r > g ? r : g;
    if (b > max) max = b;
    
    int min = r < g ? r : g;
    if (b < min) min = b;
    
    if (max == 0) {
        *h = 0;
        *s = 0;
        *v = 0;
        return;
    }
    
    if (max == min) {
        *h = 0;
    } else {
        if (max == r && g >= b) {
            *h = (g - b) * 600 / (max - min);
        } else if (max == r && g < b) {
            *h = ((g - b) * 60 / (max - min) + 360) * 10;
        } else if (max == g) {
            *h = ((b - r) * 60 / (max - min) + 120) * 10;
        } else {
            *h = ((r - g) * 60 / (max - min) + 240) * 10;
        }
        
        while (*h < 0) {
            *h += 3600;
        }
        while (*h >= 3600) {
            *h -= 3600;
        }
    }
    
    *s = (max - min) * 255 / max;
    *v = max;
}