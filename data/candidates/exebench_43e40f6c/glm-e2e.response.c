int obdRevConvert_0C(float arg1, int32_t *out1, int32_t *out2, int32_t *out3) {
    // Multiply the float argument by a constant (loaded from memory)
    // The constant at 0x2004 is likely 2.0f or similar, represented here as a placeholder
    arg1 *= 2.0f; 

    // Convert float to 64-bit integer
    int64_t temp = (int64_t)arg1;

    // First output: quotient of division by 256
    if (out1 != NULL) {
        *out1 = (int32_t)(temp / 256);
    }

    // Second output: remainder of division by 256
    if (out2 != NULL) {
        *out2 = (int32_t)(temp % 256);
    }

    // The third pointer argument (originally in %rdx) is not used in this function body
    // The function always returns 2
    return 2;
}