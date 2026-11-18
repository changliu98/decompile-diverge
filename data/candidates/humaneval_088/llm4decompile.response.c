void func0(int array[], int size, int **out_array, int *out_size) {
    *out_size = size;
    if (size == 0) {
        *out_array = NULL;
        return;
    }
    *out_array = (int*) malloc((long) size * sizeof(int));
    if (*out_array == NULL) {
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        (*out_array)[i] = array[i];
    }
    int sum = array[0] + array[size - 1];
    int is_odd = sum % 2;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (is_odd) {
                if ((*out_array)[i] > (*out_array)[j]) {
                    int temp = (*out_array)[i];
                    (*out_array)[i] = (*out_array)[j];
                    (*out_array)[j] = temp;
                }
            } else {
                if ((*out_array)[i] < (*out_array)[j]) {
                    int temp = (*out_array)[i];
                    (*out_array)[i] = (*out_array)[j];
                    (*out_array)[j] = temp;
                }
            }
        }
    }
}