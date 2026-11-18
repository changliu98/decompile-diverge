void DoAdjust(int *a, int *b, int c, int d, int e, int f) {
    (*a)--;
    (*b)--;
    *a += c;
    
    if (*a < 0) {
        *a = e - *a;
        *b -= *a / e;
        *a -= *a / e;
    }
    
    *b += *a / e;
    *a %= e;
    *b += d;
    (*a)++;
    (*b)++;
}