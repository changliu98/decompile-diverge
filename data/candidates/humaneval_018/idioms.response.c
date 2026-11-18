int func0(char *str, char *sub)
{
  int count = 0;
  int str_len = strlen(str);
  int sub_len = strlen(sub);
  int i;
  if (str_len == 0)
    return 0;
  for (i = 0; i <= str_len - sub_len; i++)
    if (strncmp(str + i, sub, sub_len) == 0)
      count++;
  return count;
}