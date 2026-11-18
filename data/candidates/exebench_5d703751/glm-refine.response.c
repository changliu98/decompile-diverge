void __cdecl iw_restrict_to_range(int min_val, int max_val, int *pvar)
{
    if (*pvar < min_val)
        *pvar = min_val;
    else if (*pvar > max_val)
        *pvar = max_val;
}