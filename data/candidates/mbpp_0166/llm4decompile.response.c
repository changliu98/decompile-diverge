int func0(int *A, int N) {
    int i, j, count = 0;
    for (i = 0; i < N; i++) {
        for (j = i + 1; j < N; j++) {
            if ((A[i] ^ A[j]) % 2 == 0) {
                count++;
            }
        }
    }
    return count;
}