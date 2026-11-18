bool __cdecl matchbrack(const char *pat, int sc, int folded)
{
  int hi; // [rsp+8h] [rbp-28h]
  bool compl; // [rsp+13h] [rbp-1Dh]
  int pc; // [rsp+14h] [rbp-1Ch]
  const char *pata; // [rsp+20h] [rbp-10h] BYREF

  pata = pat;
  compl = 0;
  if ( *pat == 33 || *pata == 94 )
  {
    compl = 1;
    ++pata;
  }
  if ( *pata == 93 )
  {
    if ( sc == 93 )
      return !compl;
    ++pata;
  }
  else if ( *pata == 45 )
  {
    if ( sc == 45 )
      return !compl;
    ++pata;
  }
  pc = *(pata - 1);
  while ( *pata != 93 )
  {
    if ( *pata != 45 || pata[1] == 93 )
    {
      pc = utf8get(&pata);
      if ( pc == sc || pc == folded )
        return !compl;
    }
    else
    {
      ++pata;
      hi = utf8get(&pata);
      if ( pc <= sc && sc <= hi || pc <= folded && folded <= hi )
        return !compl;
    }
  }
  return compl;
}