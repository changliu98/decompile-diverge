int func0(int n) {
    int flag1 = 0;
    int flag2 = 0;
    if (n % 2 == 0) {
        flag1 = 1;
    }
    if (n >= 8) {
        flag2 = 1;
    }
    return flag1 && flag2;
}