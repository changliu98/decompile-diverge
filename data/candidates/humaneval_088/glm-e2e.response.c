void func0(int *array, int n, int **out_ptr, int *out_size) {
    *out_size = n;
    if (n == 0) {
        *out_ptr = NULL;
        return;
    }
    
    *out_ptr = (int *)malloc(n * sizeof(int));
    if (*out_ptr == NULL) {
        exit(1);
    }
    
    for (int i = 0; i < n; i++) {
        (*out_ptr)[i] = array[i];
    }
    
    int is_odd = (array[0] + array[n - 1]) % 2 == 1;
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (is_odd) {
                if ((*out_ptr)[i] > (*out_ptr)[j]) {
                    int temp = (*out_ptr)[i];
                    (*out_ptr)[i] = (*out_ptr)[j];
                    (*out_ptr)[j] = temp;
                }
            } else {
                if ((*out_ptr)[i] < (*out_ptr)[j]) {
                    int temp = (*out_ptr)[i];
                    (*out_ptr)[i] = (*out_ptr)[j];
                    (*out_ptr)[j] = temp;
                }
            }
        }
    }
}