__attribute__((used)) static inline int chan_sts_suspended(u32 status)
{
	return ((status & IOAT_CHANSTS_STATUS) == IOAT_CHANSTS_SUSPENDED);
}