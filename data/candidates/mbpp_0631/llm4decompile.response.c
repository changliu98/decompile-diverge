void func0(char *text)
{
 int i;

 for (i = 0; text[i] != '\0'; i++)
  if (text[i] == ' ')
   text[i] = '_';
}