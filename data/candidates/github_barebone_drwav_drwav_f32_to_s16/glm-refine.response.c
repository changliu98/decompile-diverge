void __cdecl drwav_f32_to_s16(drwav_int16 *pOut, const float *pIn, size_t sampleCount)
{
    for (size_t i = 0; i < sampleCount; ++i)
    {
        float x = pIn[i];
        float clamped;

        // Clamp the floating-point sample to the [-1.0, 1.0] range
        if (x < -1.0f)
        {
            clamped = -1.0f;
        }
        else if (x > 1.0f)
        {
            clamped = 1.0f;
        }
        else
        {
            clamped = x;
        }

        // Scale to 16-bit unsigned integer range [0, 65535], 
        // then cast to signed 16-bit integer range [-32768, 32767] via bitwise addition.
        pOut[i] = (drwav_int16)((int)(32767.5f * (clamped + 1.0f)) + 0x8000);
    }
}