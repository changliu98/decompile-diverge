static inline uint32_t cpu_core_index_of_thread(uint64_t v)
{
	return (uint32_t)(v >> QDIO_MAX_BUFFERS_SHIFT);
}