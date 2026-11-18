static long func0(long *x, long *y, long *z, long *c, long s1, long s2) {
    long t;

    do {
        if (s2 - s1 <= 2) {
            t = kth(x + s1, y + s1, z + s1, c, s2 - s1);
            x[0] = t;
            return t;
        }
        t = kth(x + s1, y + s1, z + s1, c, (s2 - s1) / 2);
        t = kth(x + s1, y + s1, z + s1, c, (s2 - s1) / 2);
        if (z - x + s1 < s2) {
            long t2 = kth(x, y, z, c, s2 - (z - x + s1));
            if (t2 < t)
                t = t2;
        }
        t = kth(x, y, z, c, s1);
    } while (1);
    return t;
}