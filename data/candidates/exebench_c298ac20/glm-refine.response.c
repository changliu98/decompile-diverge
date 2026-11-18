void __cdecl swap_double(double *a, double *b)
{
    __int64 t = *(__int64 *)a;
    *(__int64 *)a = *(__int64 *)b;
    *(__int64 *)b = t;
}