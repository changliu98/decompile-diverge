void limit2_u16(unsigned short *ptr, unsigned short min_val, unsigned short max_val) {
    if (*ptr >= max_val) {
        *ptr = max_val;
    } else if (*ptr <= min_val) {
        *ptr = min_val;
    }
}