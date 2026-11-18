/*
 * Configure the I2S master clock (MCLK) divider.
 *
 * @param div The desired MCLK divider value.
 * @param out Pointer to the register value to be modified.
 *            The function updates the MCLK divider field within this register.
 *
 * @return 0 on success, -1 if the divider value is invalid.
 */
int i2s_sf_mclkdiv(int mclk_divider, int *register_value)
{
    switch (mclk_divider) {
    /* Special case: Divider of 1 maps to specific hardware encoding */
    case 1:
        *register_value |= 0x14000000;
        return 0;
    /* Special case: Divider of 3 maps to specific hardware encoding */
    case 3:
        *register_value |= 0x13000000;
        return 0;
    /* Special case: Divider of 5 maps to specific hardware encoding */
    case 5:
        *register_value |= 0x12000000;
        return 0;
    /* Special case: Divider of 14 (0xe) maps to specific hardware encoding */
    case 0xe:
        *register_value |= 0xe000000;
        return 0;
    default:
        /*
         * For other dividers, the value must be even.
         * Odd dividers greater than 5 are not supported.
         */
        if (mclk_divider % 2 != 0) {
            return -1;
        }
        /* Calculate the internal divider index */
        int divider_index = mclk_divider / 2;
        /*
         * Check for reserved or unsupported divider indices.
         * These specific values are excluded by hardware design.
         */
        if (divider_index == 0x15 || divider_index == 0x14 || divider_index == 0x13 || divider_index == 0xf) {
            return -1;
        }
        /*
         * Set the MCLK divider field in the register.
         * The field is 5 bits wide, located at bits [22:18].
         * The value is (d - 1), masked to 5 bits, and shifted to position.
         */
        *register_value = (divider_index - 1 & 0x1f) << 0x18 | *register_value;
        return 0;
    }
}