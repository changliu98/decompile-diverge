void drwav_f64_to_s32(int32_t* pOut, const double* pIn, uint64_t sampleCount) {
    // If either pointer is NULL, return immediately
    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (uint64_t i = 0; i < sampleCount; ++i) {
        // 0x7b17(%rip) points to a double constant, likely 2147483648.0 (0x41E0000000000000)
        // It multiplies the input by this scale factor to map the [-1.0, 1.0] range to [-2^31, 2^31]
        double scaled = pIn[i] * 2147483648.0;
        
        // cvttsd2si converts with truncation towards zero
        int32_t converted = (int32_t)scaled;
        
        // Post-increment pointer assignment
        *pOut++ = converted;
    }
}