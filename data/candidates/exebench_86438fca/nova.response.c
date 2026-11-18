static inline void atomic_sub(struct cpu_mask_set *set, int cpu)
{
	set->used -= cpu;
}