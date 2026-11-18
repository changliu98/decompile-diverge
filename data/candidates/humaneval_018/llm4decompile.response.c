int func0(char *str, char *substring)
{
 int i, str_len, sub_len, c;

 str_len = strlen(str);
 sub_len = strlen(substring);

 c = 0;
 for (i = 0; i <= str_len - sub_len; i++)
 {
  if (!strncmp(str + i, substring, sub_len))
   c++;
 }

 return c;
}