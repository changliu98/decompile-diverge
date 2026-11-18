void __cdecl drwav_s24_to_s32(drwav_int32 *pOut, const drwav_uint8 *pIn, size_t sampleCount)
{
    if (pOut && pIn)
    {
        for (size_t i = 0; i < sampleCount; ++i)
        {
            // Read 3 bytes (24-bit sample) and shift it into the top 32 bits.
            // This preserves the sign bit because arithmetic right shifts 
            // will extend the 24-bit sign bit to the full 32 bits.
            pOut[i] = (pIn[3 * i + 2] << 24) | (pIn[3 * i + 1] << 16) | (pIn[3 * i] << 8);
        }
    }
}