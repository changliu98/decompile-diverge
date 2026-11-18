static inline void SetBitInt(struct cpuidle_coupled *coupled, int cpu)
{
	coupled->online_cpus |= 1 << cpu;
}