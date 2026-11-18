void zywrleCalcSize(unsigned long long *x, unsigned long long *y, int n)
{
    *x &= ~((1 << n) - 1);
    *y &= ~((1 << n) - 1);
}