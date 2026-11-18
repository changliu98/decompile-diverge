const char *__cdecl func0(int interval1_start, int interval1_end, int interval2_start, int interval2_end)
{
  int v5; // [rsp+0h] [rbp-30h]
  int v6; // [rsp+4h] [rbp-2Ch]
  int i; // [rsp+8h] [rbp-28h]
  int l; // [rsp+Ch] [rbp-24h]

  if ( interval1_start <= interval2_start )
    v6 = interval2_start;
  else
    v6 = interval1_start;
  if ( interval1_end >= interval2_end )
    v5 = interval2_end;
  else
    v5 = interval1_end;
  l = v5 - v6;
  if ( v5 - v6 < 2 )
    return (const char *)&unk_2004;
  for ( i = 2; i * i <= l; ++i )
  {
    if ( !(l % i) )
      return (const char *)&unk_2004;
  }
  return (const char *)&unk_2007;
}