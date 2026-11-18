int paeth_predictor(int a, int b, int c) {
    int x, y, z, max;
    int sum = a + b - c;
    if (sum > a)
        x = sum - a;
    else
        x = a - sum;
    y = x;
    if (sum > b)
        z = sum - b;
    else
        z = b - sum;
    y = z;
    if (sum > c)
        z = sum - c;
    else
        z = c - sum;
    if (x <= y && x <= z)
        max = a;
    else if (y <= x && y <= z)
        max = b;
    else
        max = c;
    return max;
}