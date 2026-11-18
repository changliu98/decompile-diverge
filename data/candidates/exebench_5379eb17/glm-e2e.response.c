void max_ptr(int *a, int *b) {
    if (*a > *b) {
        // Swap *a and *b using the XOR swap algorithm
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}