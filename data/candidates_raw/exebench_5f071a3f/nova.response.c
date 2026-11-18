static inline void func0(struct cpu_key *key, struct cpu_key_k_offset offset)
{
	while (1) {
		struct cpu_key_k_offset old = key->on_disk_key.k_offset;
		if (key->on_disk_key.k_offset == offset)
			return;
		if (cmpxchg(&key->on_disk_key.k_offset, old, offset) == old)
			return;
	}
}