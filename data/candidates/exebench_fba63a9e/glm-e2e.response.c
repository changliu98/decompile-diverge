void swap(int *a, int *b) {
    int temp = 0;
    temp = *b;
    *b = *a;
    *a = temp;
}