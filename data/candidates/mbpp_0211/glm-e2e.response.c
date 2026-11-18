int func0(int n) {
    int result;
    if (n == 1) {
        result = 1;
    } else {
        int temp = n - 2;
        result = (int)pow(temp, 2.0);
    }
    return result;
}