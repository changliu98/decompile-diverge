int func0(int n) {
    int a = 1;
    int b = 2;
    int i = 0;
    int ret = 0;

    while (i < n) {
        // Update Fibonacci sequence
        int next = a + b;
        a = b;
        b = next;

        // Primality check
        int is_prime = 1;
        for (int j = 2; j * j <= b; j++) {
            if (b % j == 0) {
                is_prime = 0;
                break;
            }
        }

        if (is_prime) {
            i++;
        }

        if (i == n) {
            ret = b;
            break;
        }
    }

    return ret;
}