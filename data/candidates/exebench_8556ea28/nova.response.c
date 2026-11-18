static inline void sum(int n, struct hlist_head *h)
{
	if (!h)
		return;
	h->n += n;
}