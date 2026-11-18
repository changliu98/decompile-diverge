void __cdecl htonf(float *x)
{
    *(uint32_t *)x = htonl(*(uint32_t *)x);
}