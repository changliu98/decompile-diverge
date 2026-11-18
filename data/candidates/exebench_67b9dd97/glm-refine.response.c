float __cdecl v_inner(float *v1, float *v2, int n)
{
    float innerprod = 0.0f;
    
    for (int i = 0; i < n; ++i)
    {
        innerprod += v1[i] * v2[i];
    }
    
    return innerprod;
}