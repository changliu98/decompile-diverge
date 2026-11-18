char *__cdecl truncate_string_at_char(char *str, char chr)
{
  char *ptr; // [rsp+0h] [rbp-18h]

  for ( ptr = str; *ptr; ++ptr )
  {
    if ( *ptr == chr )
      *ptr = 0;
  }
  return str;
}