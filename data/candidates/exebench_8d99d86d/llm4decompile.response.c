void decode6(long n, long width, long height, long *x, long *y)
{
    long w, D, col;

    w = (width - 4) / 6;
    if (n >= w * height * 6) {
        D = width - w * 6;
        col = w;
    } else {
        D = 6;
        col = n / (height * 6);
    }
    n -= col * height * 6;
    *x = col * 6 + n % D;
    *y = (height - 1) - n / D;
}