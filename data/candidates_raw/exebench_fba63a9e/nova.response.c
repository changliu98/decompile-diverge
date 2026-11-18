void func0(int *a, int *b) {
    int tmp = 0;
    tmp = *b;
    *b = *a;
    *a = tmp;
}