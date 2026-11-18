static inline void func0(u64 *v, u64 mask)
{
	u64 val, new;

	val = *v;
	for (;;) {
		if (val & mask) {
			new = val ^ mask;
			if (cmpxchg64(v, val, new) == val)
				break;
			val = new;
		}
		cpu_relax();
	}
}