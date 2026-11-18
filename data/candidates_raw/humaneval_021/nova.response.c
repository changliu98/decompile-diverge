void func0(float *array, int size) {
    float max = array[0];
    float min = array[0];
    int i;
    int j;
    for (i = 1; i < size; i++) {
        if (array[i] > max)
            max = array[i];
        if (array[i] < min)
            min = array[i];
    }
    for (j = 0; j < size; j++) {
        array[j] = (array[j] - max) / (min - max);
    }
}