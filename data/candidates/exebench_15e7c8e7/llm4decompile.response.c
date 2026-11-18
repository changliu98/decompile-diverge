void j2gcal(int *y, int *m, int *d, double j)
{
 int x, n, l, i;

 x = (int)(j + 0.5) + 6940416;
 n = 4 * x / 146097;
 x -= (146097 * n + 3) / 4;
 l = 4000 * (x + 1) / 1461001;
 x -= 1461 * l / 4 - 31;
 i = 80 * x / 2447;
 *d = x - 2447 * i / 80;
 *m = i / 11;
 *y = 4 * n - 49 + l + i / 11;
}