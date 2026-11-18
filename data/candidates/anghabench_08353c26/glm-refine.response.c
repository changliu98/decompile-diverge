int __cdecl clip_f15(int v)
{
    if (v < -32767)
        return -32767;
    if (v > 32767)
        return 32767;
    return v;
}