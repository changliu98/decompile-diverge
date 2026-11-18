int func0(int n) {
    long nextN = (long)floor(sqrt((double)(2 * n)) + 0.5);
    return nextN * (nextN + 1) / 2 > n ? (int)nextN : (int)nextN + 1;
}