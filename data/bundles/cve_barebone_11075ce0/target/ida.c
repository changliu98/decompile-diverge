char *__cdecl isis_print_id(const uint8_t *cp, int id_len)
{
  unsigned __int8 *v2; // rax
  char *v3; // rax
  unsigned __int8 *v4; // rax
  char *pos; // [rsp+8h] [rbp-18h]
  int i; // [rsp+10h] [rbp-10h]

  pos = (char *)&isis_print_id_id;
  for ( i = 1; i <= 6; ++i )
  {
    v2 = (unsigned __int8 *)cp++;
    snprintf(pos, 21 - (pos - (char *)&isis_print_id_id), "%02x", *v2);
    pos += strlen(pos);
    if ( i == 2 || i == 4 )
    {
      v3 = pos++;
      *v3 = 46;
    }
  }
  if ( id_len >= 7 )
  {
    v4 = (unsigned __int8 *)cp++;
    snprintf(pos, 21 - (pos - (char *)&isis_print_id_id), ".%02x", *v4);
    pos += strlen(pos);
  }
  if ( id_len == 8 )
    snprintf(pos, 21 - (pos - (char *)&isis_print_id_id), "-%02x", *cp);
  return (char *)&isis_print_id_id;
}