
void
j2gcal(int *y, int *m, int *d, double j)
{
    int i;
    int l;
    int n;
    int x;


    l = (int)(j+0.5) + 68569;
    n = (4 * l) / 146097;
    l -= ((146097 * n) + 3) / 4;
    i = (4000 * (l + 1)) / 1461001;
    l -= (1461 * i) / 4 - 31;
    x = (80 * l) / 2447;
    *d = l - (2447 * x) / 80;
    l = x / 11;
    *m = x + 2 - (12 * l);
    *y = 100 * (n - 49) + i + l;

    return;
}
