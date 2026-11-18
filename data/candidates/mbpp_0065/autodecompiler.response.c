int func0(int *array, int length) {
    int ret = 0;
    int i = 0;
    while (1) {
        if (i >= length) break;
        if (array[i] < 0) {
            int tmp = 0 - array[i];
            i++;
            ret += func0(array + i, tmp);
            i += tmp - 1;
        } else {
            ret += array[i];
        }
        i++;
    }
    return ret;
}