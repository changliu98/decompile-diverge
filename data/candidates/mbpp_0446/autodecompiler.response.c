int func0(int *a, int asize, int *b, int bsize) {
    int i, j;
    int count = 0;

    for (i = 0; i < asize; i++) {
        for (j = 0; j < bsize; j++) {
            if (a[i] == b[j]) {
                count++;
                break;
            }
        }
    }

    return count;
}