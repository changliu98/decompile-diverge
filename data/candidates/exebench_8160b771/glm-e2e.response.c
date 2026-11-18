void int_swap(int *a, int *b) {
    int temp_a = *a;
    int temp_b = *b;
    *a = temp_b;
    *b = temp_a;
}