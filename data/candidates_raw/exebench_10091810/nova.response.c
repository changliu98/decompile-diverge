void func0(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
    t = *(a + 1);
    *(a + 1) = *(b + 1);
    *(b + 1) = t;
    t = *(a + 2);
    *(a + 2) = *(b + 2);
    *(b + 2) = t;
}