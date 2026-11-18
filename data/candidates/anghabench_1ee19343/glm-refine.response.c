bool __cdecl is_ioat_suspended(uint64_t status)
{
    return (status & IOAT_CHANSTS_STATUS) == IOAT_CHANSTS_SUSPENDED;
}