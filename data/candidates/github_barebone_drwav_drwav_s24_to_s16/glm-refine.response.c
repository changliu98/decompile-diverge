void __cdecl drwav_s24_to_s16(drwav_int16 *pOut, const drwav_uint8 *pIn, size_t sampleCount)
{
    for (size_t i = 0; i < sampleCount; ++i)
    {
        // Reconstruct the 24-bit signed integer from 3 little-endian bytes
        int sample = (pIn[3 * i + 2] << 24) | (pIn[3 * i + 1] << 16) | (pIn[3 * i] << 8);
        
        // Arithmetic right shift to sign-extend from 24 bits to 32 bits,
        // then right shift by 16 to scale down to 16 bits.
        pOut[i] = (drwav_int16)(sample >> 16);
    }
}