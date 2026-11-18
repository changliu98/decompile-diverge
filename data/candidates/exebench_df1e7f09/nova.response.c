static inline int a_inc(struct iavf_ring *ring)
{
	return ring->next_to_use++;
}