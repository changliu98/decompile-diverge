int func0(int p, int q, int N) {
    int r;
    for (int i = 0; i < N; i++) {
        r = (p * 10) / q;
        p = (p * 10) % q;
    }
    return r;
}