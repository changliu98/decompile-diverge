bool __cdecl is_ioat_suspended(unsigned __int64 status)
{
  return (IOAT_CHANSTS_STATUS & status) == IOAT_CHANSTS_SUSPENDED;
}