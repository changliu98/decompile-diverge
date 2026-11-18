static inline size_t func0(int num_sges)
{
	return sizeof(struct ib_sge) + sizeof(struct ib_sge64) * (num_sges - 1);
}