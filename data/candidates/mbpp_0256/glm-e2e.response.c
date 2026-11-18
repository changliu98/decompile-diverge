int func0(int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (i > 1) {
            int is_prime = 1;
            for (int j = 2; j < i; j++) {
                if (i % j == 0) {
                    is_prime = 0;
                    break;
                }
            }
            if (is_prime) {
                count++;
            }
        }
    }
    return count;
}