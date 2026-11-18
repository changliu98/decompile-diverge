int jrand_(int *a, int *b, int *c, int *d) {
    int result;
    
    *b = (*b * 0xab) % 0x763d;
    *c = (*c * 0xac) % 0x7663;
    *d = (*d * 0xaa) % 0x7673;
    
    jrand_.x = (double)*b / 30269.0 + (double)*c / 30307.0 + (double)*d / 30323.0;
    jrand_.u = jrand_.x - (double)(int)jrand_.x;
    
    result = (int)((double)*a * jrand_.u + 1.0);
    
    return result;
}