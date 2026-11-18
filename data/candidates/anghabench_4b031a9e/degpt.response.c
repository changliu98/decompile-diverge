int valid_bo_pre_v2(long input_value)
{
    // Extract bits 2 and 4 from the value
    unsigned int bit_mask = input_value & 0x14U;
    // If neither bit 2 nor bit 4 is set, the value is valid
    if (bit_mask == 0) return 1;
    // If only bit 2 is set, bit 1 must not be set
    if (bit_mask == 4) return (input_value & 2U) == 0;
    // If only bit 4 is set, bit 3 must not be set
    if (bit_mask == 0x10) return (input_value & 8U) == 0;
    // If both bits 2 and 4 are set, the value must be exactly 0x14
    return input_value == 0x14;
}