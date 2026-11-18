static inline int foo(struct iavf_ring *ring)
{
	return ring->next_to_use++;
}