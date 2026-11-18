int foo(int *a, int *b) {
    int old_a = *a;
    *a = *a + 1;
    int old_b = *b;
    *b = *b + 1;
    return old_a + old_b;
}