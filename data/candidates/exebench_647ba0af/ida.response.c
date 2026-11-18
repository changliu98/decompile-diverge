char *__cdecl replace_char(char *str, char find, char replace)
{
  char *current_pos; // [rsp+8h] [rbp-18h]

  for ( current_pos = strchr(str, find); current_pos; current_pos = strchr(current_pos + 1, find) )
    *current_pos = replace;
  return str;
}