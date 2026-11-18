int check(int *array, int size) {
    int i, odd = 0;
    for (i = 0; ; i++) {
        if (i >= size) break;
        if (array[i] % 2 != 0) {
            odd++;
        }
    }

    int result;
    if (odd % 2 != 0) result = 1;
    else result = 2;

    return result;
}