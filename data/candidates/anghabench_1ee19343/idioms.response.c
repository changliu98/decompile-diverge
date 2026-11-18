static inline int is_ioat_suspended(unsigned long status)
{
  return (IOAT_CHANSTS_STATUS & status) == IOAT_CHANSTS_SUSPENDED;
}