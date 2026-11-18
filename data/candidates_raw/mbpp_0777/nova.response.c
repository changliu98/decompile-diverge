int func0(int *array, int size) {
    qsort(array, size, sizeof(int), compare);
    int sum = array[0];
    for (int i = 0; i < size - 1; i++) {
        if (array[i]!= array[i + 1])
            sum += array[i + 1];
        else
            continue;
    }
    return sum;
}