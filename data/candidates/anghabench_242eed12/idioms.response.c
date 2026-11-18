static int wacom_intuos_id_mangle(int tool_id)
{
    return (tool_id & 0xfff) | ((tool_id & ~0xfff) << 4);
}