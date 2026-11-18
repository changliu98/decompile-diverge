__attribute__((used)) static inline int is_ioat_suspended(u32 status)
{
	return ((status & IOAT_CHANSTS_STATUS) == IOAT_CHANSTS_SUSPENDED);
}