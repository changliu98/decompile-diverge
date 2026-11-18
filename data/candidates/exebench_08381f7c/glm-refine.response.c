void __cdecl vscal(float *a, float ca, float *v)
{
    v[0] = a[0] * ca;
    v[1] = a[1] * ca;
    v[2] = a[2] * ca;
}