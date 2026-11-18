void func0(int *a, int *b) {
    int temp = *a;
    if (*a < *b) {
        *a = *b;
        *b = temp;
    }
}