uint32_t denormal_addf1(uint32_t a, uint32_t b) {
    uint32_t result;
    uint32_t exp;
    uint32_t mantissa;
    uint32_t shifted_b;

    // If 'a' is a denormal (or zero), just add 'b' to 'a' directly.
    if (a < 0x800000) {
        result = a + b;
    } else {
        // Extract the 8-bit exponent
        exp = (a & 0x7f800000) >> 23;

        // If exp - 1 > 31, return 'a' as is.
        // This avoids massive shifts and handles Inf/NaN (exp=255) safely.
        if (exp - 1 > 31) {
            result = a;
        } else {
            // Shift 'b' right by (exp - 1)
            shifted_b = b >> (exp - 1);

            // If the shifted 'b' becomes zero, return 'a' as is.
            if (shifted_b == 0) {
                result = a;
            } else {
                // Extract the 23-bit mantissa and add the hidden leading 1
                mantissa = (a & 0x7fffff) | 0x800000;

                // Add the shifted 'b' to the mantissa
                mantissa = mantissa + shifted_b;

                // If the mantissa overflows the 24-bit limit, normalize it
                if (mantissa >= 0x1000000) {
                    mantissa = mantissa >> 1;
                    exp = exp + 1;
                }

                // Recombine the exponent and the 23-bit mantissa
                result = (exp << 23) | (mantissa & 0x7fffff);
            }
        }
    }

    return result;
}