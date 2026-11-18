void drwav_u8_to_s16(drwav_int16* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    size_t i;
    for (i = 0; i < sampleCount; i += 1) {
        pOut[i] = (pIn[i] << 8) - 0x8000;
    }
}