int func0(int A, int N, int L, int R) {
    int i;
    int count = 0;
    for (i = L; i <= R; i++) {
        if (i % A != 0) {
            count++;
        }
        if (count == N) {
            return i;
        }
    }
    return i;
}