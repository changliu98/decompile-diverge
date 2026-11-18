int func0(int n) {
    int res;
    int x;
    int arr[100];
    int count = 0;
    int i;
    int j;

    if (n <= 2) {
        res = n;
        return res;
    }

    x = n * 2;

    // Collect divisors of n
    for (i = n; i > 1; i--) {
        if (i * 2 > n) {
            arr[count] = i;
            count++;
        }
    }

    // Find the smallest divisor d of x such that gcd(d, n) > 1
    for (j = 0; j < count; j++) {
        if (x % arr[j] != 0) {
            x = n + x;
            break;
        }
        if (j == count - 1 && x % arr[j] == 0) {
            res = x;
            return res;
        }
    }

    // Fallback loop (effectively an infinite loop in this context)
    while (1) {
        // Empty
    }
}