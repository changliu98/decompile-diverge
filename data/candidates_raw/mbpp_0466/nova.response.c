static inline void func0(struct hlist_head *hash, unsigned int size)
{
	memset(hash, 0, sizeof(struct hlist_head) * size);
}