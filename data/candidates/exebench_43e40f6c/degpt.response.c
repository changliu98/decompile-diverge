int obdRevConvert_0C(float input_value, uint *integer_part, uint *fractional_part, uint *unused_param_c, uint *unused_param_d)
{
    // Multiply input value by a constant scaling factor
    float scaled_value = DAT_00102004 * input_value;
    
    // Extract the integer part (high byte) and store in A
    *integer_part = (uint)((long)scaled_value / 0x100);
    
    // Extract the fractional part (low byte) and store in B
    *fractional_part = (uint)((long)scaled_value % 0x100);
    
    // Return status code indicating success
    return 2;
}