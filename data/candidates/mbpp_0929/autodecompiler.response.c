int func0(int array[], int size, int element) {
    int count = 0;
    int i = 0;
    while (1) {
        if (i >= size) break;
        if (array[i] == element) count++;
        i++;
    }
    return count;
}