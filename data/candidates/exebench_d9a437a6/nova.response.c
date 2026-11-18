static inline u32 do_csum(unsigned long iova, u32 pte_val, u32 pte_idx)
{
	if (iova & 2)
		pte_idx += 1;
	return pte_idx;
}