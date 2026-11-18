int obdRevConvert_42(float input_value, uint *high_byte, uint *low_byte, uint *unused_C, uint *unused_D)
{
    // Multiply input value by a constant scaling factor
    float scaled_value = DAT_00102004 * input_value;
    // Extract the high byte of the scaled value and store in A
    *high_byte = (uint)((long)scaled_value / 0x100);
    // Extract the low byte of the scaled value and store in B
    *low_byte = (uint)((long)scaled_value % 0x100);
    // Return status code indicating success
    return 2;
}