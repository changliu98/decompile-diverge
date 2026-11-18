int func0(int a, int b) {
    int x, y, z, g;
    if (a < b)
        x = a;
    else
        x = b;
    y = x;
    if (a > b)
        z = a;
    else
        z = b;
    g = z;
    if (y == 0)
        return g;
    if (z == 1)
        return 1;
    return func0(y, z % y);
}