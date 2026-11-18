bool func0(int *arr, int n) {
    int *copy = malloc(n * sizeof(int));
    
    // Copy the original array
    for (int i = 0; i < n; i++) {
        copy[i] = arr[i];
    }
    
    // Sort the copied array using bubble sort
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (copy[i] > copy[j]) {
                int temp = copy[i];
                copy[i] = copy[j];
                copy[j] = temp;
            }
        }
    }
    
    // Check if the sorted elements form a consecutive sequence
    bool is_consecutive = true;
    for (int i = 1; i < n; i++) {
        if (copy[i] != copy[i - 1] + 1) {
            is_consecutive = false;
            break;
        }
    }
    
    free(copy);
    return is_consecutive;
}