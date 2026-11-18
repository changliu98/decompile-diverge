static inline u32 cpu_map__id_to_cpu(u32 r)
{
	return (r >> 0) & 0xffff;
}