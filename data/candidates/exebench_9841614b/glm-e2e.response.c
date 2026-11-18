int UnpackImmediate(unsigned int val, unsigned int *out_val, unsigned int *out_shift) {
    if (val == 0) {
        *out_val = 0;
        *out_shift = 0;
        return 1;
    }

    for (unsigned int shift = 0; shift < 15; shift++) {
        if ((val & 0x3) != 0) {
            if (val < 0x100) {
                *out_val = val;
                *out_shift = shift;
                return 1;
            } else {
                return 0;
            }
        }
        val >>= 2;
    }

    return 0;
}