int func0(int n) {
    int result;
    if (n == 1) {
        result = 0;
    } else {
        result = n ^ func0(phi(n));
    }
    return result;
}