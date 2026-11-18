void func0(int a, int b, int c, int d, int *e, int *f) {
    if (a == c) {
        *e = -1;
    } else {
        *e = (a < c) ? a : c;
    }
    
    if (b == d) {
        *f = -1;
    } else {
        *f = (b > d) ? b : d;
    }
}