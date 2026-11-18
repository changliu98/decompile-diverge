void __cdecl limit2_i32(int *x, int lower, int upper)
{
    if (*x <= lower)
        *x = lower;
    else if (*x >= upper)
        *x = upper;
}