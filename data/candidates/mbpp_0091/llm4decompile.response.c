int func0(char **str1, char *sub_str, int size)
{
 int i;
 for (i = 0; i < size; i++)
  if (strstr(str1[i], sub_str))
   return 1;
 return 0;
}