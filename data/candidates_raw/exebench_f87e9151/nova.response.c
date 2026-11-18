void func0(int *index, float *array, float value, int size) {
    float diff, min_diff;
    int i;

    min_diff = array[0] - value;
    min_diff = min_diff * min_diff;
    *index = 0;
    for (i = 1; i < size; i++) {
        diff = array[i] - value;
        diff = diff * diff;
        if (diff < min_diff) {
            min_diff = diff;
            *index = i;
        } else {
            break;
        }
    }
}