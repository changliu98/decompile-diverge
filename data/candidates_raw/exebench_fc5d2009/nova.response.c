void func0(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}