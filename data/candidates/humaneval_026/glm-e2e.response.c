int* func0(int* arr, int n, int* out_count) {
    int* result = (int*)malloc(n * sizeof(int));
    int* seen = (int*)calloc(n, sizeof(int));
    int* duplicates = (int*)calloc(n, sizeof(int));
    
    int unique_count = 0;
    int dup_count = 0;
    int res_count = 0;
    
    // First pass: Separate elements into 'duplicates' and 'seen' arrays
    for (int i = 0; i < n; i++) {
        int val = arr[i];
        int is_dup = 0;
        
        // Check if already marked as a duplicate
        for (int j = 0; j < dup_count; j++) {
            if (duplicates[j] == val) {
                is_dup = 1;
                break;
            }
        }
        
        if (is_dup) {
            continue;
        }
        
        int is_seen = 0;
        // Check if already seen once
        for (int j = 0; j < unique_count; j++) {
            if (seen[j] == val) {
                is_seen = 1;
                break;
            }
        }
        
        if (is_seen) {
            // If seen once, move it to the duplicates array
            duplicates[dup_count++] = val;
        } else {
            // If never seen, add it to the seen array
            seen[unique_count++] = val;
        }
    }
    
    // Second pass: Build the result array with elements that are not duplicates
    for (int i = 0; i < n; i++) {
        int val = arr[i];
        int is_dup = 0;
        
        for (int j = 0; j < dup_count; j++) {
            if (duplicates[j] == val) {
                is_dup = 1;
                break;
            }
        }
        
        if (!is_dup) {
            result[res_count++] = val;
        }
    }
    
    *out_count = res_count;
    
    free(seen);
    free(duplicates);
    
    return result;
}