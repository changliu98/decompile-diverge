void drwav_s24_to_f32(void *out, void *in, unsigned long sampleCount)
{
    float *outFloat = (float*)out;
    unsigned char *inByte = (drwav_uint8*)in;
    if (outFloat == ((void *)0) || inByte == ((void *)0))
        return;
    for (unsigned long i = 0; i < sampleCount; i++)
    {
        unsigned int sample = (inByte[i * 3 + 0] << 8) | (inByte[i * 3 + 1] << 16) | (inByte[i * 3 + 2] << 24);
        float sampleFloat = (float)(sample & 0xff) * (1.0 / (float)0x7f);
        *(outFloat++) = sampleFloat;
    }
}