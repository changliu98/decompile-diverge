int func0(char *text)
{
 int i;
 int len = strlen(text);
 for (i = 0; i < len / 2; i++)
  if (text[i] != text[len - 1 - i])
   return 0;
 return 1;
}