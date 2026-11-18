static inline void atomic_inc(struct cpu_key *key)
{
	key->on_disk_key.k_offset++;
}