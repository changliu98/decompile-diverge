int func0(int *array, int size, int num) {
    int i = 0;
    char bFound = 0;

    while (!bFound && i < size) {
        if (array[i] >= num) {
            bFound = 1;
        } else {
            i++;
        }
    }

    return bFound;
}