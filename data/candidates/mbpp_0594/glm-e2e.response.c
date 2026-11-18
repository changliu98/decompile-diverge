int func0(int *arr, int n) {
    int first_even = -1;
    int first_odd = -1;
    int i;

    // Find the first even number
    for (i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            first_even = arr[i];
            break;
        }
    }

    // Find the first odd number
    for (i = 0; i < n; i++) {
        if (arr[i] % 2 != 0) {
            first_odd = arr[i];
            break;
        }
    }

    return first_even - first_odd;
}