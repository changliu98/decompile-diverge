void conv_sign(int mask, int *val) {
    if (*val & mask) {
        *val = (mask << 1) - *val;
        *val = *val * -1;
    }
}