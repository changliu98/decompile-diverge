static inline u8 spc_used(u8 ring_start, u8 ring_stop, u8 ring_max)
{
	int free;

	free = ring_start - ring_stop;
	if (free <= 0)
		free += ring_max + 1;	
	return free;
}