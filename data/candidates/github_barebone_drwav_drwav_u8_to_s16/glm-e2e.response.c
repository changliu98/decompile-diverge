void drwav_u8_to_s16(int16_t* dst, const uint8_t* src, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        uint8_t u8 = src[i];
        int32_t s32 = (u8 << 8) - 0x8000;
        dst[i] = (int16_t)s32;
    }
}