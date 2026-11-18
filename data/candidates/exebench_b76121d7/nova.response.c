static inline void atomic_or_long(struct hash_entry *p, unsigned long flag)
{
	p->flag |= flag;
}