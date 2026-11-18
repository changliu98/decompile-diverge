DRWAV_API void drwav_u8_to_f32(float* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

#ifdef DR_WAV_LIBSNDFILE_COMPAT
    /*
    It appears libsndfile uses slightly different logic for the u8 -> f32 conversion to dr_wav, which in my opinion is incorrect. It appears
    libsndfile performs the conversion something like "f32 = (u8 / 256) * 2 - 1", however I think it should be "f32 = (u8 / 255) * 2 - 1" (note
    the divisor of 256 vs 255). I use libsndfile as a benchmark for testing, so I'm therefore leaving this block here just for my automated
    correctness testing. This is disabled by default.
    */
    for (i = 0; i < sampleCount; ++i) {
        *pOut++ = (pIn[i] / 256.0f) * 2 - 1;
    }
#else
    for (i = 0; i < sampleCount; ++i) {
        float x = pIn[i];
        x = x * 0.00784313725490196078f;    /* 0..255 to 0..2 */
        x = x - 1;                          /* 0..2 to -1..1 */

        *pOut++ = x;
    }
#endif
}