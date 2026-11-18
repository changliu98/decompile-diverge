int obdRevConvert_31(float input_value, uint *high_byte, uint *low_byte, uint *unused_C, uint *unused_D)
{
    // Convert float value to integer and extract high byte into A
    *high_byte = (uint)((long)input_value / 0x100);
    // Extract low byte into B
    *low_byte = (uint)((long)input_value % 0x100);
    // Return number of bytes processed
    return 2;
}