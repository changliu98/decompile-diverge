int func0(int *arr, int arr_size, int target) {
    int max_dist = arr_size - 1;
    
    // Sort the array using qsort
    // Note: The assembly passes strcmp as the comparison function, which is 
    // unusual for an integer array but faithfully represented here.
    qsort(arr, arr_size, sizeof(int), (int (*)(const void *, const void *))strcmp);
    
    for (int i = 0; i < arr_size; i++) {
        int found_idx = find_ind(arr[i], i, arr_size, target, arr);
        
        if (found_idx != -1) {
            int dist = found_idx - i + 1;
            int remaining = arr_size - dist;
            
            if (max_dist < remaining) {
                max_dist = max_dist; // No-op, but explicitly matches the assembly's branch
            } else {
                max_dist = remaining;
            }
        }
    }
    
    return max_dist;
}