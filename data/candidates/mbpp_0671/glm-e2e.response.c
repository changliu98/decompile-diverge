int func0(int n) {
    if (n == 0) {
        return 1;
    }
    
    if ((n & (n + 1)) == 0) {
        return n;
    }
    
    int k = (int)log2((double)(n & -n)) + 1;
    return n | (1 << (k - 1));
}