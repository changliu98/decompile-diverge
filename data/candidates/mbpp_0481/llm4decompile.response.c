int func0(int set[], int n, int sum)
{
    if (sum == 0)
        return 1;
    if (n == 0)
        return 0;
    if (set[n-1] > sum)
        return func0(set, n-1, sum);

    return func0(set, n-1, sum) || func0(set, n-1, sum - set[n-1]);
}