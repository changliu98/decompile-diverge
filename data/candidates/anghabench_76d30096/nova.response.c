static inline size_t sizeof_ns2_led_priv(int entries)
{
	return sizeof(struct dlm_slot) + entries * sizeof(struct dlm_slot_map);
}