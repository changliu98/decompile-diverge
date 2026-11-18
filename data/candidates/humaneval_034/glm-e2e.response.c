int* func0(int* arr, int n, int* out_size) {
    int* unique_arr = (int*)malloc(n * sizeof(int));
    int unique_count = 0;
    
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (arr[i] == unique_arr[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            unique_arr[unique_count] = arr[i];
            unique_count++;
        }
    }
    
    for (int i = 0; i < unique_count - 1; i++) {
        for (int j = i + 1; j < unique_count; j++) {
            if (unique_arr[i] > unique_arr[j]) {
                int temp = unique_arr[i];
                unique_arr[i] = unique_arr[j];
                unique_arr[j] = temp;
            }
        }
    }
    
    *out_size = unique_count;
    return unique_arr;
}