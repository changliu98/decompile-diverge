int func0(float *ptr, int low, int high) {
    int i, j;
    i = low;
    j = low + 1;
    while (j <= high) {
        if (ptr[i] > ptr[j]) {
            i = j;
        }
        j++;
    }
    return i;
}