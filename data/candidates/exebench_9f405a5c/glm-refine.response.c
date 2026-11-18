void __cdecl copyvector(float *a, float *b)
{
    *(float4*)a = *(float4*)b;
}