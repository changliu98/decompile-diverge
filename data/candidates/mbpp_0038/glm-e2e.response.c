double func0(int *arr, int n) {
    int first_even = -1;
    int first_odd = -1;
    int i, j;

    /* Find first even number */
    for (i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            first_even = arr[i];
            break;
        }
    }

    /* Find first odd number */
    for (j = 0; j < n; j++) {
        if (arr[j] % 2 != 0) {
            first_odd = arr[j];
            break;
        }
    }

    if (first_even == -1 || first_odd == -1) {
        return -1.0;
    }

    return (double)first_even / (double)first_odd;
}