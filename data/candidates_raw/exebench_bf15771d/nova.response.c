int func0(int *a, int *n) {
    int sum = 0, max = 0, max_so_far = 0, i = 0, j = 1;
    while (1) {
        if (*n < i / 2) {
            if (a[i] > 0) {
                sum += a[i];
                max = max_so_far = sum;
                if (max_so_far > i / 2) {
                    *n = max_so_far;
                    return max;
                }
            } else if (sum == *n) {
                return max;
            }
        } else {
            i++;
            j *= 2;
        }
    }
}