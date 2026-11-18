char * replace_char(char *str,char find,char replace)

{
  char *current_pos;
  char replace_local;
  char find_local;
  char *str_local;
  
  for (current_pos = strchr(str,(int)find); current_pos != (char *)0x0;
      current_pos = strchr(current_pos + 1,(int)find)) {
    *current_pos = replace;
  }
  return str;
}