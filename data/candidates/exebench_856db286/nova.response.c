static inline int _hclib_atomic_dec_relaxed(struct iavf_ring *ring)
{
	return (ring->next_to_use++) - 1;
}