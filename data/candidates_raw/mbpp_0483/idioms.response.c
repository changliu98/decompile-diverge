int find_factor(int n)
{
    int i; int fact = 1;
    for (i = 1; i < n; i++) {
        fact *= i;
        if (fact % n == 0)
            return i;
    }
    return i - 1;
}