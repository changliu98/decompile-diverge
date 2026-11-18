static void reverseIntRange(int *a, int *b, int n) {
    int tmp = *a;
    *a = n - *b;
    *b = n - tmp;
}