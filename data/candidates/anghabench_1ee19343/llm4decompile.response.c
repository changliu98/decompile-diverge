int is_ioat_suspended(unsigned long status)
{
	return (status & IOAT_CHANSTS_STATUS) == IOAT_CHANSTS_SUSPENDED;
}