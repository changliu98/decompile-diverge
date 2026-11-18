double __cdecl Mat_doubleSwap(double *a)
{
    unsigned long long val = *(unsigned long long *)a;
    *(unsigned long long *)a = ((val & 0x00FF00FF00FF00FFULL) << 8) | ((val >> 8) & 0x00FF00FF00FF00FFULL);
    return *a;
}