void numpar(double *arr, int *n_ptr, int *remaining_ptr) {
    int n = *n_ptr;
    // Allocate a Variable Length Array (VLA) of size `n`
    // The assembly aligns the stack pointer to 16 bytes and allocates space for `n` ints.
    int removed[n]; 
    
    int i = -1;
    int j;
    int k;
    int removed_count = -1;
    double diff = 0.0;

    while (i < n - 1) {
        i++;
        j = 0;
        while (j < removed_count) {
            if (i == removed[j]) {
                i++;
            }
            j++;
        }

        k = i + 1;
        while (k < n) {
            j = 0;
            while (j < removed_count) {
                if (k == removed[j]) {
                    k++;
                }
                j++;
            }

            diff = arr[i] - arr[k];
            if (0.0 > diff) {
                diff *= -1.0;
            }

            if (diff == 0.0) {
                removed_count++;
                removed[removed_count] = k;
                (*remaining_ptr)--;
            }
            k++;
        }
    }
}