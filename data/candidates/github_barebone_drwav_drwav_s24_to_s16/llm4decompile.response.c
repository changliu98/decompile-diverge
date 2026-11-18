void drwav_s24_to_s16(drwav_int16* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    size_t i;
    for (i = 0; i < sampleCount; i += 1) {
        drwav_uint32 sample = (drwav_uint32)(pIn[i*3 + 0] << 16) | (drwav_uint32)(pIn[i*3 + 1] << 8) | (drwav_uint32)(pIn[i*3 + 2]);
        pOut[i] = (drwav_int16)((sample >> 8) & 0xFFFF);
    }
}