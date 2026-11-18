int func0(int a, int b, int c) {
    int flag;
    if (a + b > c && a + c > b && b + c > a) {
        flag = 1;
    } else {
        flag = 0;
    }
    return flag;
}