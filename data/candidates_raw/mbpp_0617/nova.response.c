int func0(int a, int b, int c) {
    int x, y, z, ans;
    x = a;
    y = b;
    if (a < b)
        z = a;
    else
        z = b;
    a = x;
    b = z;
    if (a > b)
        y = a;
    else
        y = b;
    b = y;
    if (c >= b)
        ans = (c + b - 1) / b;
    else if (c == 0)
        ans = 0;
    else if (c == a)
        ans = 1;
    else
        ans = 2;
    return ans;
}