static inline size_t sizeof_pwm_leds_priv(int num_sges)
{
	return sizeof(struct ib_sge) + sizeof(struct ib_sge64) * (num_sges - 1);
}