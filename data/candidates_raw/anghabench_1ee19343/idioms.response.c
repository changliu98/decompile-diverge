static inline int ioat_chansts_is_suspended(unsigned long status)
{
  return (IOAT_CHANSTS_STATUS & status) == IOAT_CHANSTS_SUSPENDED;
}