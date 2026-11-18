void qr_getSize(int w, int h, int *p1, int *p2, int *p3) {
    *p1 = w;
    *(p1 + 1) = w; // or p1[1] = w;
    
    *p3 = h;
    
    *p2 = w;
    *(p2 + 1) = h; // or p2[1] = h;
}