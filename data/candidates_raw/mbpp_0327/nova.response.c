int func0(int a, int b, int c) {
    int flag;
    if (a == b || b == c || c == a)
        flag = 1;
    else
        flag = 0;
    return flag;
}