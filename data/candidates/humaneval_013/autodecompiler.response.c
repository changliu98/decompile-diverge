int func0(int u, int v) {
    while (v != 0) {
        int t = u % v;
        u = v;
        v = t;
    }
    return u;
}