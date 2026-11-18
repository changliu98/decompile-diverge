int i2s_sf_sclkdiv(int div, unsigned int *reg) {
    int ret;
    int val;

    if (div == 1) {
        *reg |= 0x800000;
        ret = 0;
    } else if (div == 3) {
        *reg |= 0x900000;
        ret = 0;
    } else if (div % 2 != 0) {
        ret = -1;
    } else {
        val = (div / 2) - 1;
        if (val == 8 || val == 9) {
            ret = -1;
        } else {
            *reg |= ((div / 2 - 1) << 20) & 0xf00000;
            ret = 0;
        }
    }

    return ret;
}