int func0(int a, int b) {
    if (b < 0) {
        return -func0(a, -b);
    } else if (b == 0) {
        return 0;
    } else if (b == 1) {
        return a;
    } else {
        return a + func0(a, b - 1);
    }
}