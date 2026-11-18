void func0(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}