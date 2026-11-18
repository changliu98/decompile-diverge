void ComputeReverb16(short *src, short *dst, long nSamples, long strength)
{
    long i;
    long tmp;

    for (i = nSamples; i > 0; i--)
    {
        tmp = *dst + (*src * strength) / 100;
        if (tmp > 32767)
            tmp = 32767;
        else if (tmp < -32768)
            tmp = -32768;
        *dst++ = tmp;
        *src++;
    }
}