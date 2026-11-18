int func0(int *arr, int n) {
    int max = 0, sum = 0, i = 0, j, k, l, m, x, y, z;
    for (i = 0; i < n; i++) {
        x = arr[i];
        if (x > 1) {
            for (j = 1;; j++) {
                for (k = 2; k * k <= x; k++) {
                    if (x % k == 0) {
                        j = 0;
                        break;
                    }
                }
                if (j!= 0) {
                    if (x > max)
                        max = x;
                    else
                        max = max;
                    max = max;
                    break;
                }
            }
        }
    }
    while (max > 0) {
        sum = sum + max % 10;
        max = max / 10;
    }
    return sum;
}