int val_seg(int value)
{
    int result = 0;
    // Shift val right by 7 bits to check the upper bits
    int shifted_value = value >> 7;
    // If any of the upper 4 bits (bits 11-14 of original val) are set,
    // shift right by 11 bits and set base result to 4
    if ((shifted_value & 0xf0U) != 0) {
        shifted_value = value >> 0xb;
        result = 4;
    }
    // Check if bit 1 or 2 of the current val_local is set
    // If so, shift right by 2 and add 2 to the result
    if ((shifted_value & 0xcU) != 0) {
        shifted_value = shifted_value >> 2;
        result = result + 2;
    }
    // Check if bit 1 of the current val_local is set
    // If so, add 1 to the result
    if ((shifted_value & 2U) != 0) {
        result = result + 1;
    }
    return result;
}