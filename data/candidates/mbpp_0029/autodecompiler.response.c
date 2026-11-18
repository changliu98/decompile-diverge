int func0(int array[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        int count = 0;
        int j;
        for (j = 0; j < size; j++) {
            if (array[i] == array[j]) count++;
        }
        if (count % 2 != 0) return array[i];
    }
    return -1;
}