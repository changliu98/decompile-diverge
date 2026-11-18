static inline size_t func0(int entries)
{
	return sizeof(struct dlm_slot) + entries * sizeof(struct dlm_slot_map);
}