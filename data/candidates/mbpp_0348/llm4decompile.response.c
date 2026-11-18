unsigned long long func0(int M)
{
    int n = M / 2;
    return bin_coff(2 * n, n) / (n + 1);
}