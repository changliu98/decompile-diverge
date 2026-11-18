static inline void set_bit(struct cpuidle_coupled *coupled, int i)
{
	coupled->ready_waiting_states |= (1 << i);
}