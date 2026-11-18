static inline void bmp_iter_next(u64 *v)
{
	*v = *v >> 1;
}