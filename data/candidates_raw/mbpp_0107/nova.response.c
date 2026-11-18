int func0(int a, int b) {
    int i, j, k, l, m, n;

    n = 0;
    for (i = a; i <= b; i++) {
        if (i < 10)
            continue;
        if (i < 16) {
            n++;
            continue;
        }
        if (i >= 16) {
            for (j = i; j > 0; j /= 16) {
                if (j % 16 < 10)
                    break;
                n++;
            }
        }
    }

    return n;
}