void __cdecl func0(int a, int b, int *out, int *size)
{
    int lower = (a < b) ? a : b;
    int upper = (a < b) ? b : a;
    
    *size = 0;
    
    // The loop starts at 'lower' (which is >= 0). 
    // Therefore, 'i < 10' is redundant and we only need to check i <= 9.
    for (int i = lower; i <= upper && i <= 9; ++i)
    {
        if (!(i % 2)) // If 'i' is even
        {
            out[(*size)++] = i;
        }
    }
}