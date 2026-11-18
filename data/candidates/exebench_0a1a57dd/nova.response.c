static inline void htonf(void *_u)
{
	__le32 *u = _u;
	u[0] = le32_to_cpu(u[0]);
}