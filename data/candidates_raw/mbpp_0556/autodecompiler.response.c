int getOddOneOut(int *arr, int len) {
    int i, j;
    int oddPair = 0;

    for (i = 0; i < len; i++) {
        for (j = i + 1; j < len; j++) {
            if ((arr[i] ^ arr[j]) % 2 != 0) {
                oddPair++;
            }
        }
    }

    return oddPair;
}