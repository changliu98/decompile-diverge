void merge(int *arr1, int *arr2, int *out) {
    int i = 0;
    int j = 0;
    int k = 0;

    // Main merge loop: continues as long as both arrays have elements left
    while (i < 6 && j < 6) {
        if (arr1[i] < arr2[j]) {
            out[k++] = arr1[i++];
        } else {
            out[k++] = arr2[j++];
        }
    }

    // Copy any remaining elements from the first array
    while (i < 6) {
        out[k++] = arr1[i++];
    }

    // Copy any remaining elements from the second array
    while (j < 6) {
        out[k++] = arr2[j++];
    }
}