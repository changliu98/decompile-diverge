int func0(int *array, int size) {
    int i, j;
    int mode, max_count = 0;
    int current_count;
    qsort__bench(array, size, sizeof(int), qcompare);
    for (i = 0; i < size; i++) {
        current_count = 0;
        for (j = 0; j < size; j++) {
            if (array[j] == array[i]) {
                current_count++;
            }
        }
        if (current_count > max_count) {
            max_count = current_count;
            mode = array[i];
        }
    }
    return mode;
}