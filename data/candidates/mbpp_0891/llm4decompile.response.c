int func0(int A, int B) {
    while (A > 0 && B > 0) {
        A /= 10;
        B /= 10;
    }
    if (A == 0 && B == 0) {
        return 1;
    } else {
        return 0;
    }
}