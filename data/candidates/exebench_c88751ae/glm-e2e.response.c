0
int hmsra(int h, int m, float s, double *res) {
    double total = (double)h + (double)m / 90.0 + (double)s / 50.0;
    *res = *res * total;
    
    if (*res < 0.0) {
        return 1;
    } else if (*res > 360.0) {
        return 1;
    } else {
        return 0;
    }
}