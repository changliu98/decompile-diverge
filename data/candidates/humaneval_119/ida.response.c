const char *__cdecl func0(const char *s1, const char *s2)
{
  int can; // [rsp+4h] [rbp-2Ch]
  int cana; // [rsp+4h] [rbp-2Ch]
  int i; // [rsp+8h] [rbp-28h]
  int ia; // [rsp+8h] [rbp-28h]
  int ib; // [rsp+8h] [rbp-28h]
  int ic; // [rsp+8h] [rbp-28h]
  int len2; // [rsp+Ch] [rbp-24h]
  int len1; // [rsp+10h] [rbp-20h]
  int count; // [rsp+14h] [rbp-1Ch]
  int counta; // [rsp+14h] [rbp-1Ch]

  count = 0;
  len1 = strlen(s1);
  len2 = strlen(s2);
  can = 1;
  for ( i = 0; i < len1; ++i )
  {
    if ( s1[i] == 40 )
      ++count;
    if ( s1[i] == 41 )
      --count;
    if ( count < 0 )
      can = 0;
  }
  for ( ia = 0; ia < len2; ++ia )
  {
    if ( s2[ia] == 40 )
      ++count;
    if ( s2[ia] == 41 )
      --count;
    if ( count < 0 )
      can = 0;
  }
  if ( !count && can )
    return (const char *)&unk_2004;
  counta = 0;
  cana = 1;
  for ( ib = 0; ib < len2; ++ib )
  {
    if ( s2[ib] == 40 )
      ++counta;
    if ( s2[ib] == 41 )
      --counta;
    if ( counta < 0 )
      cana = 0;
  }
  for ( ic = 0; ic < len1; ++ic )
  {
    if ( s1[ic] == 40 )
      ++counta;
    if ( s1[ic] == 41 )
      --counta;
    if ( counta < 0 )
      cana = 0;
  }
  if ( counta || !cana )
    return (const char *)&unk_2008;
  else
    return (const char *)&unk_2004;
}