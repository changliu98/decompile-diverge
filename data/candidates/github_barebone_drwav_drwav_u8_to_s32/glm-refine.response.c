void __cdecl drwav_u8_to_s32(drwav_int32 *pOut, const drwav_uint8 *pIn, size_t sampleCount)
{
    if (pOut && pIn)
    {
        for (size_t i = 0; i < sampleCount; ++i)
        {
            // Convert unsigned 8-bit PCM (0-255) to signed 32-bit PCM
            // Center the wave to 0 by subtracting 128, then shift to the highest 8 bits of the 32-bit integer
            pOut[i] = ((drwav_int32)pIn[i] - 128) << 24;
        }
    }
}