int* func0(int* arr1, int n, int* arr2, int m, int* out_size) {
    int* result = (int*)malloc(n * sizeof(int));
    int result_count = 0;

    // Find elements in arr1 that are not in arr2 and add them to result
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < result_count; j++) {
            if (result[j] == arr1[i]) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            for (int j = 0; j < m; j++) {
                if (arr1[i] == arr2[j]) {
                    result[result_count++] = arr1[i];
                    break;
                }
            }
        }
    }

    // Sort the result array in ascending order using bubble sort
    for (int i = 0; i < result_count - 1; i++) {
        for (int j = 0; j < result_count - i - 1; j++) {
            if (result[j] > result[j + 1]) {
                int temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
            }
        }
    }

    *out_size = result_count;
    return result;
}