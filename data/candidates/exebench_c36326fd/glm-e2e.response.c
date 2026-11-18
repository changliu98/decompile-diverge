void initialize_temp(int *dst, int *src) {
    int i = 9;
    int j = 14;

    // First loop: copies elements from src to dst in reverse order
    while (i >= 0) {
        dst[j] = src[i];
        i--;
        j--;
    }

    // Second loop: fills the remaining elements at the beginning of dst with 0
    while (j + 1 != 0) {
        j--;
        dst[j + 1] = 0;
    }
}