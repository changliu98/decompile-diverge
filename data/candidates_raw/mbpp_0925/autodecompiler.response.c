int multiply(int array[], int size) {
    int result = 1;
    int i = 0;
    while (1) {
        if (i >= size) break;
        result *= array[i];
        i++;
    }
    return result;
}