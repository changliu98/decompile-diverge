int func0(int u, int v) {
    int t, f = 1;
    if (u % v == 0)
        return v;
    while (v > 0) {
        if (u % 2 == 0 && v % 2 == 0)
            f *= 2;
        else if (u % 2 == 0 && v % 2 != 0)
            break;
        else if (u % 2 != 0 && v % 2 == 0)
            break;
        else {
            t = (u - v) / 2;
            u = v;
            v = t;
        }
    }
    return f * u;
}