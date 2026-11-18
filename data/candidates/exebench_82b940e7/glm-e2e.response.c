void clamp(int *a, int *b, int c) {
    *b += *a / c;
    *a %= c;
}