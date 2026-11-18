int __cdecl func0(const char *txt)
{
  unsigned __int8 second_last_char; // [rsp+Ah] [rbp-16h]
  unsigned __int8 last_char; // [rsp+Bh] [rbp-15h]
  int len; // [rsp+Ch] [rbp-14h]

  len = strlen(txt);
  if ( !len )
    return 0;
  last_char = txt[len - 1];
  if ( ((*__ctype_b_loc())[last_char] & 0x400) == 0 )
    return 0;
  if ( len == 1 )
    return 1;
  second_last_char = txt[len - 2];
  return ((*__ctype_b_loc())[second_last_char] & 0x400) == 0;
}