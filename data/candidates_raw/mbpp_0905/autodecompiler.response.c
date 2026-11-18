int binomial(int n)
{
    int top = factorial(n + 1, n);
    int bottom = factorial(1, n);
    return top / bottom;
}