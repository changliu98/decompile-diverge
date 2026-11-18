int func0(int n) {
    int max_product = 0;
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < n; j++) {
            int k = n - i - j;
            if (i * j * k > max_product) {
                max_product = i * j * k;
            }
        }
    }
    return max_product;
}