void TH_float2halfbits(const float *src, uint16_t *dest) {
    uint32_t f32_bits;
    memcpy(&f32_bits, src, sizeof(float));

    // Extract absolute value and sign
    uint32_t abs_f32 = f32_bits & 0x7FFFFFFF;
    uint16_t sign = (f32_bits >> 16) & 0x8000;

    // Check for NaN (exponent == 255, mantissa != 0)
    if (abs_f32 > 0x7F800000) {
        *dest = 0x7FFF; // Canonical NaN
        return;
    }

    // Check for overflow (abs_f32 > 65520.0)
    if (abs_f32 > 0x477FEFFF) {
        *dest = sign | 0x7C00; // Infinity
        return;
    }

    // Check for underflow (abs_f32 < 2^-24, the smallest subnormal half precision)
    if (abs_f32 < 0x33000001) {
        *dest = sign; // Zero
        return;
    }

    uint32_t f_exp = (abs_f32 >> 23) & 0xFF;
    uint32_t f_mantissa = f32_bits & 0x7FFFFF;
    
    uint32_t shift;
    uint16_t half_exp;
    uint32_t working_mantissa;

    if (f_exp <= 0x70) { 
        // Subnormal half-precision
        shift = 126 - f_exp;
        half_exp = 0;
        working_mantissa = f_mantissa | 0x800000; // Add implicit leading 1
    } else { 
        // Normal half-precision
        shift = 13;
        half_exp = f_exp - 112; // Bias difference: 127 - 15 = 112
        working_mantissa = f_mantissa;
    }

    // Calculate rounding (round to nearest, ties to even)
    uint32_t lsb_s1 = (1u << shift) >> 1;
    uint32_t remainder = working_mantissa & ((1u << shift) - 1);
    uint16_t half_mantissa = working_mantissa >> shift;

    if (remainder > lsb_s1 || (remainder == lsb_s1 && (half_mantissa & 1))) {
        half_mantissa++;
        // If rounding caused mantissa to overflow into the exponent bit
        if ((half_mantissa & 0x400) != 0) {
            half_exp++;
            half_mantissa = 0;
        }
    }

    *dest = sign | (half_exp << 10) | half_mantissa;
}