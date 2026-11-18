int foo(int *a, int *b, int c) {
    *a = *a * 2;
    *b = *b / 2;
    return *a + *b;
}