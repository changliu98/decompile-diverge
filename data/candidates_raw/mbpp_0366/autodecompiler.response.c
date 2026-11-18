int max_product(int *nums, size_t length) {
    int max = nums[0] * nums[1];
    for (size_t i = 1; i < length - 1; i++) {
        int product = nums[i] * nums[i + 1];
        if (product > max) {
            max = product;
        }
    }
    return max;
}