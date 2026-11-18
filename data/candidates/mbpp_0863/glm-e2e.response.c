int func0(int *arr, int n) {
    int max_len = 0;
    int current_len = 0;
    int i, j;
    int temp;

    // Bubble sort
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Remove duplicates
    int *unique = malloc(n * sizeof(int));
    int unique_count = 0;
    
    unique[unique_count++] = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] != arr[i - 1]) {
            unique[unique_count++] = arr[i];
        }
    }

    // Find the length of the longest consecutive sequence
    for (i = 0; i < unique_count; i++) {
        if (i > 0 && unique[i] == unique[i - 1] + 1) {
            current_len++;
        } else {
            current_len = 1;
        }
        if (max_len < current_len) {
            max_len = current_len;
        }
    }

    free(unique);
    return max_len;
}