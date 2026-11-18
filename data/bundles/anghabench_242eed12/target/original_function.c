int wacom_intuos_id_mangle(int tool_id)
{
	return (tool_id & ~0xFFF) << 4 | (tool_id & 0xFFF);
}