int func0(int *arr, unsigned long n) {
    int max_product = arr[0] * arr[1];
    for (unsigned long i = 1; i < n - 1; i++) {
        int current_product = arr[i] * arr[i + 1];
        if (current_product > max_product) {
            max_product = current_product;
        }
    }
    return max_product;
}