void drwav_u8_to_s16(drwav_int16 *pOut, const drwav_uint8 *pIn, size_t sampleCount)
{
    for (size_t i = 0; i < sampleCount; ++i)
    {
        // Convert unsigned 8-bit PCM to signed 16-bit PCM.
        // 1. Shift left by 8 to scale the 8-bit value into the upper 8 bits of a 16-bit integer.
        // 2. Subtract 32768 (0x8000) to shift the range from [0, 65535] down to [-32768, 32767].
        pOut[i] = (pIn[i] << 8) - 32768;
    }
}