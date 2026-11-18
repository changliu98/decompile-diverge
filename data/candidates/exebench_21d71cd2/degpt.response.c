int obdRevConvert_23(float input_value, uint *high_byte, uint *low_byte, uint *unused_C, uint *unused_D)
{
    // Divide the input value by a constant to normalize it
    float normalized_value = input_value / DAT_00102004;
    
    // Extract the high byte of the normalized value and store in A
    *high_byte = (uint)((long)normalized_value / 0x100);
    
    // Extract the low byte of the normalized value and store in B
    *low_byte = (uint)((long)normalized_value % 0x100);
    
    // Return a fixed value of 2
    return 2;
}