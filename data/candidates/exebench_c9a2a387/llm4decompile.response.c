void eastero(int y, int *m, int *d)
{
    int a, b, c, e;

    a = y % 19;
    b = y / 100;
    c = y % 100;
    e = (13 + 8 * b - 13 * b / 4 + a * 19 / 23) % 30;
    e += (32 + 2 * (b % 4) + 2 * (c / 4) - e - c % 4) % 7;
    *m = 3 + (e + 24) / 31;
    *d = (e + 25) % 31 + 1;
}