void AdjustSpan(int *a, int *b, int c) {
    if (*a < 0) {
        *b += *a;
        *a = 0;
    }
    
    if (*a + *b > c) {
        *b = c - *a;
    }
}