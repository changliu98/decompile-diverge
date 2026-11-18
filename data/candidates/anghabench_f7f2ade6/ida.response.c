bool __cdecl pmc_overflow(unsigned __int64 val)
{
  return (val & 0x80000000) != 0LL;
}