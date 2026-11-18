void swap(int *a, int *b) {
    int zero_buffer = *a;
    *a = *b;
    *b = zero_buffer;
}