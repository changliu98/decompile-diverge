void func0(float *data, int *max, int *max_index, int *min, int *min_index,
             int *zero, int size) {
    int i;
    *max = 0;
    *zero = 0;
    *min_index = 0;
    *min = 0;
    *max_index = 0;
    for (i = 0; i < size; i++) {
        if (data[i] > 0) {
            (*max)++;
            if (data[i] > *min) {
                *min = data[i];
                *min_index = i;
            }
        } else {
            (*zero)++;
            if (data[i] < 0) {
                (*min)++;
                data[i] = 1;
            } else {
                if (*min > *max) {
                    *min = *max;
                    *min_index = i - *max;
                    *max = 0;
                }
            }
        }
    }
    if (*min > *max) {
        *min = *max;
        *min_index = i - *max;
    }
}