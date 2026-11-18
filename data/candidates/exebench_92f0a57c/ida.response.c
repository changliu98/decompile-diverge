double __cdecl HTS_rnd(unsigned __int64 *next)
{
  *next = 1103515245 * *next + 12345;
  return (double)(*(_DWORD *)((_BYTE *)next + 2) & 0x7FFF) / 32767.0;
}