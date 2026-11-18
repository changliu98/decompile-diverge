int func0(int n) {
    int result;
    if (n == 1) {
        result = 1;
    } else {
        result = pow(2, (n - 2)) + func0(n - 1);
    }
    return result;
}