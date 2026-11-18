void func0(int *array1, int *array2, int *diff, int length) {
    int i = 0;
    while (1) {
        if (i >= length) {
            break;
        }
        diff[i] = abs(array1[i] - array2[i]);
        i++;
    }
}