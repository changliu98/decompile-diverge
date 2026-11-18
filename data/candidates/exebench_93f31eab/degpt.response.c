int obdRevConvert_10(float input_value, uint *high_byte, uint *low_byte, uint *unused_C, uint *unused_D)
{
    // Multiply input value by a constant factor (DAT_00102004)
    float scaled_value = DAT_00102004 * input_value;
    
    // Extract the high byte of the scaled value and store in A
    *high_byte = (uint)((long)scaled_value / 0x100);
    
    // Extract the low byte of the scaled value and store in B
    *low_byte = (uint)((long)scaled_value % 0x100);
    
    // Return constant value 2
    return 2;
}