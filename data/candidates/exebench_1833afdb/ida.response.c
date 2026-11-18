void __cdecl validate_st_entry(unsigned __int64 *entry)
{
  *entry &= ~0x20uLL;
  *entry = *entry;
}