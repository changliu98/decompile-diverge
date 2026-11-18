double __cdecl arithmetic_series_sum(int first_term, int num_terms, int common_diff)
{
    // Formula: S_n = (n / 2) * [2a + (n - 1)d]
    return (double)(num_terms * (2 * first_term + (num_terms - 1) * common_diff)) / 2.0;
}