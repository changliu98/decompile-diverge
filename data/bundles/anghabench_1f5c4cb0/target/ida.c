unsigned __int64 __cdecl _reverse_ffs(unsigned __int64 word)
{
  int num; // [rsp+0h] [rbp-Ch]
  unsigned __int64 worda; // [rsp+4h] [rbp-8h]

  worda = word;
  num = 0;
  if ( (word & 0xFFFF0000) != 0 )
    worda = word >> 16;
  else
    num = 16;
  if ( (worda & 0xFF00) != 0 )
    worda >>= 8;
  else
    num += 8;
  if ( (worda & 0xF0) != 0 )
    worda >>= 4;
  else
    num += 4;
  if ( (worda & 0xC) != 0 )
    worda >>= 2;
  else
    num += 2;
  if ( (worda & 2) == 0 )
    ++num;
  return num;
}