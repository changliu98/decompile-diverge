int number_of_elements(int *array, int n, int p) {
    int i;
    int counter = 0;

    for (i = 0; ; i++) {
        if (i >= n) break;

        if ((array[i] * array[i]) % p == 1) counter++;
    }

    return counter;
}