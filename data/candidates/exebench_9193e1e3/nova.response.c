void clip_coord(int *a, int b, int c) {
    int x, y, z;
    x = a[0];
    if (x < b)
        y = b;
    else
        y = x;
    x = y;
    if (x > c)
        z = c;
    else
        z = x;
    x = z;
    a[0] = x;
}