int __cdecl wc_match_inner(const char *wildcard, const char *target, size_t target_len)
{
  const char *save_t; // [rsp+0h] [rbp-40h]
  const char *save_w; // [rsp+8h] [rbp-38h]
  int ret; // [rsp+14h] [rbp-2Ch]
  int reta; // [rsp+14h] [rbp-2Ch]
  const char *target_end; // [rsp+18h] [rbp-28h]
  const char *targeta; // [rsp+28h] [rbp-18h] BYREF
  const char *wildcarda; // [rsp+30h] [rbp-10h] BYREF

  wildcarda = wildcard;
  targeta = target;
  target_end = &target[target_len];
  if ( *wildcard != 42 )
  {
    ret = wc_match_fragment(&wildcarda, &targeta, target_end);
    if ( ret <= 0 )
      return ret;
  }
  while ( *wildcarda )
  {
    if ( *wildcarda != 42 )
      _assert_fail("*wildcard == '*'", "func.c", 0xE4u, "int wc_match_inner(const char *, const char *, size_t)");
    while ( *wildcarda == 42 )
      ++wildcarda;
    if ( !*wildcarda )
      return 1;
    reta = 0;
    while ( *targeta )
    {
      save_w = wildcarda;
      save_t = targeta;
      reta = wc_match_fragment(&wildcarda, &targeta, target_end);
      if ( reta < 0 )
        return reta;
      if ( reta > 0 && !*wildcarda && targeta != target_end )
      {
        targeta = &target_end[save_t - targeta];
        wildcarda = save_w;
        return wc_match_fragment(&wildcarda, &targeta, target_end);
      }
      if ( reta > 0 )
        break;
      ++targeta;
    }
    if ( reta <= 0 )
      return 0;
  }
  return targeta == target_end;
}