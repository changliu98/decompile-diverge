char *func0(int h, int m, int s) {
    char *(*f)(int, int, int);
    if (s * m - 4 * h > 0)
        f = &sunny;
    else if (s * m - 4 * h == 0)
        f = &sunny_s;
    else
        f = &rainy;
    return f(h, m, s);
}