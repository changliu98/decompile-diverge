void hil_s_from_xy(int x, int y, int n, int *d) {
    int i;
    int rx, ry, s, t;
    
    i = n - 1;
    while (i >= 0) {
        rx = (x >> i) & 1;
        ry = (y >> i) & 1;
        s = (ry << 1) | rx;
        
        t = (*d << 2) | ((0x361e9cb4 >> (s << 1)) & 3);
        *d = t;
        
        i--;
    }
}