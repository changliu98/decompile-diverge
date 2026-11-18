int obdRevConvert_47_4B(float val, int32_t *out1, int64_t *out2, int64_t *out3) {
    // The calculation: val * 1000.0f / 3600.0f
    // This is mathematically equivalent to val * (5.0f / 18.0f)
    *out1 = (int32_t)(val * (1000.0f / 3600.0f));
    
    // The function always returns 1
    return 1;
}