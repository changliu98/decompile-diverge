int obdRevConvert_3C_3F(float input_value, uint *high_byte, uint *low_byte, uint *unused_C, uint *unused_D)
{
    // Calculate scaled value using global constants and input value
    float scaled_value = DAT_00102004 * (DAT_00102008 + input_value);
    
    // Extract high byte of the scaled value and store in A
    *high_byte = (uint)((long)scaled_value / 0x100);
    
    // Extract low byte of the scaled value and store in B
    *low_byte = (uint)((long)scaled_value % 0x100);
    
    // Return status code indicating success
    return 2;
}