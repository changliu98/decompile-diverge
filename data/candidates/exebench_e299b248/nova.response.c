static inline void doZ(struct vring_used_elem *dst)
{
	dst->len += 16;
}