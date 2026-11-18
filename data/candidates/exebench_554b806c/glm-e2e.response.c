bool is_empty(float *array, int size) {
    for (int i = 0; i <= size; i++) {
        if (array[i] > 0.0f) {
            return false;
        }
    }
    return true;
}