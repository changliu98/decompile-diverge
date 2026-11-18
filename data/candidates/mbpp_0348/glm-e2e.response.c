long long func0(int n) {
    int half_n = n / 2;
    long long binomial_result = bin_coff(2 * half_n, half_n);
    long long result = binomial_result / (half_n + 1);
    return result;
}