int get_count(int *array, int size, int min, int max) {
    int i;
    int count = 0;

    for (i = 0; i < size; i++) {
        if (array[i] >= min && array[i] <= max) {
            count++;
        }
    }

    return count;
}