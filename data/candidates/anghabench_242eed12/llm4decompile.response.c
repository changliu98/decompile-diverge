u32 wacom_intuos_id_mangle(u32 tool_id)
{
	return ((tool_id & 0xfff000) << 4) | (tool_id & 0xfff);
}