void drwav_s32_to_s16(int16_t* dst, const int32_t* src, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        int32_t sample = src[i];
        int16_t converted = (int16_t)(sample >> 16);
        dst[i] = converted;
    }
}