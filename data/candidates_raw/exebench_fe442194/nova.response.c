void func0(int *a, int *b) {
    *b = *a ^ *b;
    *a = *a ^ *b;
    *b = *a ^ *b;
}