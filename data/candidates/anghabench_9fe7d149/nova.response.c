static inline u16 cpu_map__id_to_socket(u32 val)
{
	return val >> 16;
}