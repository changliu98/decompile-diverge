void __cdecl atomic_clear_mask(unsigned __int64 mask, unsigned __int64 *addr)
{
  *addr &= ~mask;
}