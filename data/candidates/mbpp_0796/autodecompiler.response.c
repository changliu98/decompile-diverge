int func0(int *array, int length) {
    int total = 0;
    int i = 0;

    while (1) {
        if (i >= length) {
            break;
        }
        total += array[i];
        i++;
    }

    return total;
}