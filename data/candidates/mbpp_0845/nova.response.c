int func0(int n) {
    int res;
    if (n < 1)
        res = 0;
    else if (n < 2)
        res = 1;
    else {
        double x = n * log10(n) - n * log10(18446744073709551615.0) +
                   log10(229064922537007) * n;
        res = (int)floor(x) + 1;
    }
    return res;
}