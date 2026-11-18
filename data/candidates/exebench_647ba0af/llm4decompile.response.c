char *replace_char(char *str, char find, char replace)
{
 char *current_pos;

 while ((current_pos = strchr(str, find)) != NULL)
  *current_pos = replace;

 return str;
}