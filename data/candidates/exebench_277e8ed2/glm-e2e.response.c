void calc_sth11(float *out1, float *out2) {
    // The compiler loads several constants from the .rodata section.
    // Based on the assembly addresses, the constants are:
    // 0x2004: 100.0f
    // 0x2008: -2.0f
    // 0x200c: 1.0f
    // 0x2010: 40.0f
    // 0x2014: 0.01f
    // 0x2018: 0.1f
    // 0x201c: 0.001f
    // 0x2020: 0.0f
    // 0x2024: -40.0f
    // 0x2028: -40.0 (double precision)
    
    // The compiler aggressively spills these to the stack, but effectively:
    float v1 = *out1;
    float v2 = *out2;

    // 0x1261 - 0x127e
    float temp1 = v2 * 1.0f + 0.0f;

    // 0x1283 - 0x12b6
    // (0.001f * v1 * v1 * v1) + (0.1f * v1 * v1) + 0.01f
    float temp2 = (0.001f * v1 * v1 * v1) + (0.1f * v1 * v1) + 0.01f;

    // 0x12bb - 0x12f6
    // (temp1 - 40.0f) * (-2.0f * v1 + 1.0f) + temp2
    float result1 = (temp1 - 40.0f) * (-2.0f * v1 + 1.0f) + temp2;

    // 0x12fb - 0x1319
    // if (result1 > 100.0f) result1 = 100.0f;
    if (result1 > 100.0f) {
        result1 = 100.0f;
    }

    // 0x131e - 0x1341
    // if (result1 < -40.0f) result1 = -40.0f;
    // Note: The compiler uses a double-precision -40.0 for the comparison,
    // but stores the single-precision -40.0f back to the variable.
    if (result1 < -40.0f) {
        result1 = -40.0f;
    }

    // 0x1346 - 0x135c
    *out2 = temp1;
    *out1 = result1;
}