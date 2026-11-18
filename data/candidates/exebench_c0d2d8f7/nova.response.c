static inline int g(struct iavf_ring *ring)
{
	return ring->next_to_clean++;
}