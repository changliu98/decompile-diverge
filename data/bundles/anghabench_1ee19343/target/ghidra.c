bool is_ioat_suspended(unsigned_long status)

{
  unsigned_long status_local;
  
  return (bool)((status & IOAT_CHANSTS_STATUS) == IOAT_CHANSTS_SUSPENDED);
}