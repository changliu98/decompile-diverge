int par_msquares_multi_code(int a, int b, int c, int d) {
    int counter = 0;
    
    int v1 = counter++;
    int v2;
    if (b == a) {
        v2 = v1;
    } else {
        v2 = counter++;
    }
    
    int v3;
    if (c == b) {
        v3 = v2;
    } else if (c == a) {
        v3 = v1;
    } else {
        v3 = counter++;
    }
    
    int v4;
    if (d == c) {
        v4 = v3;
    } else if (d == b) {
        v4 = v2;
    } else if (d == a) {
        v4 = v1;
    } else {
        v4 = counter++;
    }
    
    return v1 | (v2 << 2) | (v3 << 4) | (v4 << 6);
}