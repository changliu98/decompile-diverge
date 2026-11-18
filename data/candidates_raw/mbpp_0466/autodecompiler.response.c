int find_peak(int *array, int size) {
    return find_peak_util(array, 0, size - 1, size);
}