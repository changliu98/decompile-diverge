int __cdecl func0(const char *str)
{
  char ch_0; // [rsp+Bh] [rbp-415h]
  int index; // [rsp+Ch] [rbp-414h]
  int char_map[256]; // [rsp+10h] [rbp-410h] BYREF
  int count; // [rsp+414h] [rbp-Ch]
  const char *stra; // [rsp+418h] [rbp-8h]

  stra = str;
  count = 0;
  memset(char_map, 0, sizeof(char_map));
  for ( index = 0; stra[index]; ++index )
  {
    ch_0 = tolower((unsigned __int8)stra[index]);
    if ( !char_map[ch_0] && ((*__ctype_b_loc())[(unsigned __int8)ch_0] & 0x400) != 0 )
    {
      char_map[ch_0] = 1;
      ++count;
    }
  }
  return count;
}