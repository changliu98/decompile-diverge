void drwav_f64_to_s16(drwav_int16* pOut, const drwav_float64* pIn, size_t sampleCount)
{
    size_t i;
    for (i = 0; i < sampleCount; ++i) {
        drwav_float64 sample = pIn[i];





        if (sample < -1.0) {
            sample = -1.0;
        } else if (sample > 1.0) {
            sample = 1.0;
        }

        pOut[i] = (drwav_int16)((sample * 32768.0) - 32768);
    }
}