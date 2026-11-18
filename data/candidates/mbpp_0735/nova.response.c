int func0(int n) {
    int result;
    if (n == 1) {
        result = 1;
    } else {
        result = n ^ func0(predecessor(n));
    }
    return result;
}