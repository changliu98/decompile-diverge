int func0(int n) {
    int i;
    int out;

    if (n < 1) {
        out = 0;
    } else if (n == 1) {
        out = 1;
    } else {
        out = 18;
        for (i = 2; i < n; i++) {
            out *= 10;
        }
    }

    return out;
}