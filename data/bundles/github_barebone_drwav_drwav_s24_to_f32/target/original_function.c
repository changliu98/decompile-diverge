DRWAV_API void drwav_s24_to_f32(float* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        double x;
        drwav_uint32 a = ((drwav_uint32)(pIn[i*3+0]) <<  8);
        drwav_uint32 b = ((drwav_uint32)(pIn[i*3+1]) << 16);
        drwav_uint32 c = ((drwav_uint32)(pIn[i*3+2]) << 24);

        x = (double)((drwav_int32)(a | b | c) >> 8);
        *pOut++ = (float)(x * 0.00000011920928955078125);
    }
}