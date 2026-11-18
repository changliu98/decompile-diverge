int ctsxs(uint32_t f_val, int scale, uint32_t *sat_reg) {
    int exp = (f_val >> 23) & 0xFF;
    uint32_t mantissa = f_val & 0x7FFFFF;
    int result;

    // Check for NaN or Infinity (Exponent == 255, Mantissa != 0)
    if (exp == 0xFF && mantissa != 0) {
        return 0;
    }

    // Adjust exponent by bias (127) and scale factor
    exp = exp - 0x7F + scale;

    // If the resulting exponent is negative, the value is too small (rounds to 0)
    if (exp < 0) {
        return 0;
    }

    // If the resulting exponent is >= 31, the value is too large (saturation)
    if (exp >= 31) {
        // Check if the original value is exactly -2^31 (0xCF000000 when scaled)
        // If not, we need to set the saturation flag
        if (f_val + (scale << 23) != 0xCF000000) {
            *sat_reg |= VSCR_SAT;
        }

        // Saturate to the maximum or minimum 32-bit signed integer
        if (f_val & 0x80000000) {
            return 0x80000000; // -2^31
        } else {
            return 0x7FFFFFFF; // 2^31 - 1
        }
    }

    // Normal conversion path
    // Add the implicit leading 1 to the mantissa
    mantissa |= 0x800000;

    // Shift left by 7 to align the 24-bit mantissa to 31 bits, 
    // then arithmetic shift right by (30 - exp) to place the decimal point correctly
    mantissa = (mantissa << 7) >> (30 - exp);

    // Apply the sign
    if (f_val & 0x80000000) {
        return -(int)mantissa;
    } else {
        return (int)mantissa;
    }
}