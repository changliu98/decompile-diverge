int wacom_intuos_id_mangle(int input_tool_id)
{
    // Extract the upper bits of tool_id (bits 31-12) and shift them left by 4 positions
    // Extract the lower bits of tool_id (bits 11-0) and keep them as-is
    // Combine the shifted upper bits and the lower bits using bitwise OR
    return (input_tool_id & 0xfffff000U) << 4 | input_tool_id & 0xfffU;
}