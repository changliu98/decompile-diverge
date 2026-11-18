int func0(int a, int b) {
    char flag;
    while (1) {
        if (a > 0 && b > 0) {
            a = a % 10;
            b = b % 10;
        } else if (a == 0 && b == 0) {
            flag = 1;
            break;
        } else {
            flag = 0;
            break;
        }
    }
    return flag % 2;
}