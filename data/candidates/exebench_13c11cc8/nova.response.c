void sort_three(int *a, int *b, int *c) {
    int temp;
    if (*a > *b) {
        temp = *b;
        *b = *a;
        *a = temp;
    }
    if (*a > *c) {
        temp = *c;
        *c = *a;
        *a = temp;
    }
    if (*b > *c) {
        temp = *c;
        *c = *b;
        *b = temp;
    }
}