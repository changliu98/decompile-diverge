void func0(int *a, int *b) {
    if (*a!= *b) {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}