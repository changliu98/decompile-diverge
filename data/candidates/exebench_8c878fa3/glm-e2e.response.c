void sun_mjulianday_to_date(int32_t jd, int32_t *year, int32_t *month, int32_t *day) {
    int32_t l = jd + 2399857 + 32044; // 0x249f01 + 0x7d2c = 0x24BD2D = 2399857 + 32044
    int32_t n = (4 * l + 3) / 146097; // 0x23ab1 = 146097
    int32_t i = l - (4 * n + 3) / 4;
    
    int32_t j = (4 * i + 3) / 1461;   // 0x5b5 = 1461
    int32_t k = i - (4 * j + 3) / 4;
    
    int32_t m = (5 * k + 2) / 153;    // 0x99 = 153
    
    *day = k - (153 * m + 2) / 5 + 1;
    *month = m + 3 - 12 * (m / 10);
    *year = 100 * n + j - 4800 + m / 10; // 0x12c0 = 4800
}