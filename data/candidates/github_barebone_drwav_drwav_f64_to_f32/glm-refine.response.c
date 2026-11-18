void __cdecl drwav_f64_to_f32(float *pOut, const double *pIn, size_t sampleCount)
{
    if (pOut && pIn)
    {
        for (size_t i = 0; i < sampleCount; ++i)
        {
            pOut[i] = (float)pIn[i];
        }
    }
}