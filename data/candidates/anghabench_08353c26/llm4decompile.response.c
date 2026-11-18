int clip_f15(int v)
{
    if (v < -32767)
        return -32767;
    else if (v > 32767)
        return 32767;
    else
        return v;
}