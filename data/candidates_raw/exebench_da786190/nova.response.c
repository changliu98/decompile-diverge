static inline void func0(struct cpuidle_coupled *coupled, int cpu)
{
	coupled->online_cpus |= 1 << cpu;
}