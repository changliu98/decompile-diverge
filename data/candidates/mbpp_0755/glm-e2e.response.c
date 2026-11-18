double func0(double *arr, int n) {
    if (n < 2) {
        return -1.0;
    }

    int duplicate_count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                duplicate_count++;
                break;
            }
        }
    }

    if (n == 2 && duplicate_count == 1) {
        return -1.0;
    }

    double *unique_arr = (double *)malloc(n * sizeof(double));
    int unique_count = 0;
    
    for (int i = 0; i < n; i++) {
        int is_duplicate = 0;
        for (int j = 0; j < unique_count; j++) {
            if (unique_arr[j] == arr[i]) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            unique_arr[unique_count++] = arr[i];
        }
    }

    for (int i = 0; i < unique_count; i++) {
        for (int j = i + 1; j < unique_count; j++) {
            if (unique_arr[i] > unique_arr[j]) {
                double temp = unique_arr[i];
                unique_arr[i] = unique_arr[j];
                unique_arr[j] = temp;
            }
        }
    }

    double result = unique_arr[1];
    free(unique_arr);
    
    return result;
}