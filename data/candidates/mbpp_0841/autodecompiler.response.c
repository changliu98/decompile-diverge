int func0(int *array, int size) {
    int i, j;
    int inv_count = 0;

    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if (array[i] > array[j]) {
                inv_count++;
            }
        }
    }

    return inv_count;
}