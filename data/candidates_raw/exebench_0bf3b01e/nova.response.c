static void func0(int *a, int *b, int a_min, int b_min, int mod,
                           int *a_new, int *b_new) {
    *a -= 1;
    *b -= 1;
    *a += a_min;
    if (*a < 0) {
        *a = -*a + mod;
        *b -= *a / mod;
        *a %= mod;
    }
    *b += *a / mod;
    *a %= mod;
    *a_new = *a;
    *b_new = *b + b_min;
    *a += 1;
    *b += 1;
}