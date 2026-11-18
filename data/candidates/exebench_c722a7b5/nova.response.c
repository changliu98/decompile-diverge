static inline int conta_voto(struct iavf_ring *ring)
{
	return ring->next_to_use++;
}