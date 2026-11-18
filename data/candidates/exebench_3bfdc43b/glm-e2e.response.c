void norm(int *a, int *b, int c) {
    int k;
    
    if (*b < 0) {
        k = (-*b - 1) / c + 1;
        *a -= k;
        *b += k * c;
    }
    
    if (*b >= c) {
        k = *b / c;
        *a += k;
        *b -= k * c;
    }
}