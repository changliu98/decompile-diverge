int __cdecl func0(const char *test_str)
{
  int idx; // [rsp+8h] [rbp-18h]
  int length; // [rsp+Ch] [rbp-14h]
  int res; // [rsp+10h] [rbp-10h]
  int cnt; // [rsp+14h] [rbp-Ch]

  cnt = 0;
  res = 0;
  length = strlen(test_str);
  for ( idx = 0; idx < length; ++idx )
  {
    if ( ((*__ctype_b_loc())[test_str[idx]] & 0x100) != 0 )
    {
      ++cnt;
    }
    else
    {
      if ( cnt > res )
        res = cnt;
      cnt = 0;
    }
  }
  if ( ((*__ctype_b_loc())[test_str[length - 1]] & 0x100) != 0 && cnt > res )
    return cnt;
  return res;
}