void drwav_u8_to_s16(void *pOut, void *pIn, unsigned long sampleCount)
{
    short *out = (int16_t *) pOut;
    unsigned char *in = (uint8_t *) pIn;
    unsigned long i;
    for (i = 0; i < sampleCount; i++)
    {
        out[i] = in[i] * 0x100 - 0x8000;
    }
}