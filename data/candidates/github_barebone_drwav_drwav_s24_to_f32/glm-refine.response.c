void __cdecl drwav_s24_to_f32(float *pOut, const drwav_uint8 *pIn, size_t sampleCount)
{
    if (!pOut || !pIn)
        return;

    for (size_t i = 0; i < sampleCount; ++i)
    {
        // Read 3 bytes (Little-Endian)
        uint32_t byte0 = pIn[3 * i];
        uint32_t byte1 = pIn[3 * i + 1];
        uint32_t byte2 = pIn[3 * i + 2];
        
        // Combine into a 24-bit integer
        uint32_t combined = byte0 | (byte1 << 8) | (byte2 << 16);
        
        // Sign-extend from 24-bit to 32-bit
        int32_t s24 = (combined & 0x800000) ? (combined | 0xFF000000) : combined;
        
        // Convert to float and scale (0.0000001192092895507812f is 1 / 8388608.0f, or 1 / 2^23)
        *pOut++ = (float)s24 * 0.0000001192092895507812f;
    }
}