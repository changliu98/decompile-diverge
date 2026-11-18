int func0(int a, int b, int c) {
    int result;
    while (c > 0) {
        c--;
        a = a * 10;
        result = a / b;
        a = a % b;
    }
    return result;
}