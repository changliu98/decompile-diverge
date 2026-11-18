static inline void func0(struct cpu_mask_set *set, int cpu)
{
	set->used -= cpu;
}