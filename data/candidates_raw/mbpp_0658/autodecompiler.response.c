int mode(int *array, int size) {
    int mode = array[0];
    int max_count = 0;
    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (array[j] == array[i]) {
                count++;
            }
        }
        if (count > max_count) {
            max_count = count;
            mode = array[i];
        }
    }
    return mode;
}