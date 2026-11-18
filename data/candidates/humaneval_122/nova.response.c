int func0(int *array, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] >= -100 && array[i] <= 100) {
            sum += array[i];
        }
    }
    return sum;
}