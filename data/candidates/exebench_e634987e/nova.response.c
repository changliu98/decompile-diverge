static inline int increment(struct iavf_ring *ring)
{
	return ring->next_to_use++;
}