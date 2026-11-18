int func0(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return 0;
}