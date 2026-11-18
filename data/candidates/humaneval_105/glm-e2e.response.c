void func0(int *arr, int n, long **out_arr, int *out_count) {
    long lookup_table[10];
    memcpy(lookup_table, (const void *)0x3d90, 0x50); // 10 * 8 bytes

    // Bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    *out_count = 0;
    
    // Count valid elements (between 1 and 9 inclusive)
    for (int i = n - 1; i >= 0; i--) {
        if (arr[i] >= 1 && arr[i] <= 9) {
            (*out_count)++;
        }
    }

    // Allocate memory for the output array
    *out_arr = (long *)malloc(*out_count * 8);
    
    int idx = 0;
    for (int i = n - 1; i >= 0 && idx < *out_count; i--) {
        if (arr[i] >= 1 && arr[i] <= 9) {
            (*out_arr)[idx++] = lookup_table[arr[i]];
        }
    }
}