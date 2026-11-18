int func0(int a, int b) {
    int c = a / b * b;
    int d = c + b;
    int e;
    if (a - c > d - a)
        e = d;
    else
        e = c;
    return e;
}