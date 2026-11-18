int __cdecl INDMAXVAL(float *val, int start_idx, int end_idx)
{
    int max_idx = start_idx;

    for (int i = start_idx + 1; i <= end_idx; ++i)
    {
        if (val[i] > val[max_idx])
        {
            max_idx = i;
        }
    }

    return max_idx;
}