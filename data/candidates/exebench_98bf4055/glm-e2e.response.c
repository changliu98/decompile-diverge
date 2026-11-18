void reverseIntRange(int *a, int *b, int c) {
    int temp = *a;
    *a = c - *b;
    *b = c - temp;
}