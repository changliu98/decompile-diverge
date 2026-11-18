int func0(int *list1, int size) {
    int i;
    for (i = 0; i < size - 1; i++) {
        if (list1[i] > list1[i + 1]) {
            return 0;
        }
    }
    return 1;
}