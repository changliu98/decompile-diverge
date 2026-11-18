void drwav_s24_to_f32(float* pOut, const drwav_uint8* pIn, size_t totalSampleCount)
{
    drwav_uint32 i;
    drwav_uint32 sampleCount;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    sampleCount = (drwav_uint32)totalSampleCount;

    for (i = 0; i < sampleCount; ++i) {
        drwav_uint32 sample;
        drwav_int32 sample32;


        sample = ((drwav_uint32)pIn[i * 3]) << 8 | ((drwav_uint32)pIn[i * 3 + 1]) << 16 | ((drwav_uint32)pIn[i * 3 + 2]) << 24;
        sample32 = (drwav_int32)sample;


        sample32 >>= 8;


        *pOut++ = (float)((drwav_int32)sample32 / (float)(0x7FFFFF));
    }
}