void __cdecl validate_rt_entry(unsigned __int64 *entry)
{
  *entry &= ~0x20uLL;
  *entry &= 0xFFFFFFFFFFFFFF3FLL;
  *entry = *entry;
  *entry |= 3uLL;
}