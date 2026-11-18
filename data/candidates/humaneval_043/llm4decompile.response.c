int func0(int *l, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if (l[i] + l[j] == 0) {
                return 1;
            }
        }
    }
    return 0;
}