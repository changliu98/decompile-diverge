static int get_real_id(int tool_id)
{
    return (tool_id & 0xfff) | ((tool_id & ~0xfff) << 4);
}