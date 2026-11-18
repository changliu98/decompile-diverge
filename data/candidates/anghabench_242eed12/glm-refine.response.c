int __cdecl wacom_intuos_id_mangle(int tool_id)
{
    int lower_12_bits = tool_id & 0xFFF;          // Extract bits 0-11
    int upper_20_bits = tool_id & 0xFFFFF000;     // Extract bits 12-31
    
    // Shift the upper bits left by 4 (multiply by 16) and combine with the lower bits
    return lower_12_bits | (upper_20_bits << 4);
}