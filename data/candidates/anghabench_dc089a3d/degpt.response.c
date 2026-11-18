int cpu_map__id_to_socket(int cpu_id)
{
	return cpu_id >> 0x10;
}