int func0(int * array, int size) {
    int count = 0;
    int i = 0;
    while (1) {
        if (i >= size) {
            break;
        }
        if (array[i] % 2 != 0) {
            count++;
        }
        i++;
    }
    return count;
}