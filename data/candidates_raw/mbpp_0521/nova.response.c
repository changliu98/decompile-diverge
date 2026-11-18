int func0(int a, int b, int c) {
    int x;
    if (a == b || b == c || c == a)
        x = 1;
    else
        x = 0;
    return x;
}