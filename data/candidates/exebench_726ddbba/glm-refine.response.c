void __cdecl r3min(double *u, double *v)
{
    for (int i = 0; i < 3; ++i)
    {
        u[i] -= v[i];
    }
}