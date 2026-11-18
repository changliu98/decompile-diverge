int __cdecl C_Utils_compare_float_ptr(const float *item1, const float *item2)
{
    if (*item1 == *item2)
        return 0;
    
    if (*item2 > *item1)
        return -1;
        
    return 1;
}