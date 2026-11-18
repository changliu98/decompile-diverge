void zywrleCalcSize(int *arg1, int *arg2, int shift) {
    *arg1 &= ~((1 << shift) - 1);
    *arg2 &= ~((1 << shift) - 1);
}