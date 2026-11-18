void __cdecl drwav_f64_to_s16(drwav_int16 *pOut, const double *pIn, size_t sampleCount)
{
    for (size_t i = 0; i < sampleCount; ++i)
    {
        double x = pIn[i];
        double clamped;

        // Clamp x to the range [-1.0, 1.0]
        if (x < -1.0)
            clamped = -1.0;
        else if (x > 1.0)
            clamped = 1.0;
        else
            clamped = x;

        // Convert the clamped double to an unsigned 16-bit integer offset, 
        // then cast to drwav_int16 to map [0, 65535] to [0, 32767] and [-32768, -1].
        pOut[i] = (drwav_int16)((int)(32767.5 * (clamped + 1.0)) + 0x8000);
    }
}