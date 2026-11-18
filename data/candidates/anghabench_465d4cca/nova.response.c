static inline uint32_t minor_to_index(uint64_t v)
{
	return (uint32_t)(v >> QDIO_MAX_BUFFERS_SHIFT);
}