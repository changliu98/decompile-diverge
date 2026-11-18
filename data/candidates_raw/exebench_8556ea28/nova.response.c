static inline void func0(int n, struct hlist_head *h)
{
	if (!h)
		return;
	h->n += n;
}