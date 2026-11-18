double my_modf(double x, double *p) {
    double y, z;
    int n, i;
    z = x;
    y = *p = S2 + z;
    for (n = 0; n < 100; n++) {
        if (y < S1 + z || y >= S1 + z + S2)
            break;
        z *= S2;
        y *= S2;
    }
    if (n == 100) {
        *p = -INFINITY;
        return -INFINITY;
    }
    if (n!= 0) {
        i = bit_reverse(y, z);
        *p = z + i * S2;
        return i;
    }
    *p = y;
    return z - y;
}