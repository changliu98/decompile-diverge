void __cdecl table_norm(double *values, int values_len, double *thresholds, int thresholds_len, long *counts, int counts_len)
{
    int i, j;

    // Count how many thresholds are strictly less than each value
    for (i = 0; i < thresholds_len; ++i)
    {
        for (j = 0; j < values_len; ++j)
        {
            if (values[j] > thresholds[i])
            {
                ++counts[j];
            }
        }
    }

    // Ensure no count remains zero (replace 0 with 1)
    for (j = 0; j < counts_len; ++j)
    {
        if (counts[j] == 0)
        {
            counts[j] = 1LL;
        }
    }
}