void AdjustSpan2(int *a, int *b, int *c, int d) {
    if (*a < 0) {
        *c += *a;
        *b -= *a;
        *a = 0;
    }
    
    if (*a + *c > d) {
        *c = d - *a;
    }
}