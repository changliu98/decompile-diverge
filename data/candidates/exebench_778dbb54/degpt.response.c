int obdRevConvert_43(float input_value, uint *high_byte, uint *low_byte, uint *unused_C, uint *unused_D)
{
    // Calculate scaled value using global constants DAT_00102008 and DAT_00102004
    float scaled_value = (DAT_00102008 * input_value) / DAT_00102004;
    
    // Extract high byte of fVar1 and store in A
    *high_byte = (uint)((long)scaled_value / 0x100);
    
    // Extract low byte of fVar1 and store in B
    *low_byte = (uint)((long)scaled_value % 0x100);
    
    // Return constant value 2
    return 2;
}