void tigrFill(Tigr *bmp, int x, int y, int w, int h, int color) {
    if (x < 0) {
        w += x;
        x = 0;
    }
    if (y < 0) {
        h += y;
        y = 0;
    }
    
    if (x + w > bmp->w) {
        w = bmp->w - x;
    }
    if (y + h > bmp->h) {
        h = bmp->h - y;
    }
    
    if (w <= 0 || h <= 0) {
        return;
    }
    
    int *p = bmp->pix + y * bmp->w + x;
    int bw = bmp->w;
    
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            p[j] = color;
        }
        p += bw;
    }
}