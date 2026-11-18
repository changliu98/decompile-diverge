void nexper(int n, int *a, int *flag, int *even) {
    if (*flag == 0) {
        // Initialization: fill array `a` with 1, 2, ..., n
        for (int i = 1; i <= n; i++) {
            a[i] = i;
        }
        *flag = 1;
        *even = 1;
        return;
    }

    if (*even == 1) {
        // Simple swap for the even case
        int temp = a[2];
        a[2] = a[3];
        a[3] = temp;
        *even = 0;

        // Check if we are at the last permutation for n <= 3
        if (a[n] != 1 || a[2] != (n / 2) + 2) {
            return;
        }
        if (n <= 3) {
            *flag = 0;
            return;
        }

        // Check if the sequence is strictly increasing from index 1 to n-3
        for (int i = 1; i <= n - 3; i++) {
            if (a[i + 1] != a[i] + 1) {
                return;
            }
        }
        *flag = 0;
        return;
    } else {
        // Main permutation logic for the odd case
        int count = 0;
        int i, j, k, m, p, q, s, t;

        for (i = 2; i <= n; i++) {
            m = a[i];
            j = i - 1;
            count = 0;
            
            // Count how many elements before index `i` are greater than `a[i]`
            for (k = 1; k <= j; k++) {
                if (a[k] > m) {
                    count++;
                }
            }
            
            // Check parity condition
            if (count == (j + count) % 2) {
                continue;
            }

            // Calculate the offset based on the parity of count
            p = ((count + 1) / 2) * (n + 1);
            q = 0;
            s = 0;

            // Find the appropriate elements to swap
            for (k = 1; k <= j; k++) {
                int diff1 = a[k] - m;
                int diff2 = a[k] - p;
                if ((diff1 >= 0 || diff2 < 0) && (diff1 < 0 || diff2 < 0)) {
                    s = a[k];
                    q = k;
                }
            }

            // Perform the swap
            a[q] = m;
            a[i] = s;
            *even = 1;
            return;
        }

        // If the loop finishes without returning, we are back to the start
        *flag = 0;
        return;
    }
}