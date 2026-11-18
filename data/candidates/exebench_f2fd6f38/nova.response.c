int find_max_idx(float *arr) {
    float max = 0.0;
    int max_index = -1;
    int i = 0;
    while (i < 17) {
        if (arr[i] > max) {
            max = arr[i];
            max_index = i;
        }
        i++;
    }
    if (max_index >= 0) {
        max = 0.01 * max;
        i = 0;
        while (i < 17) {
            if (max_index!= i) {
                if (arr[i] > max) {
                    return -1;
                }
            }
            i++;
        }
    }
    return max_index;
}