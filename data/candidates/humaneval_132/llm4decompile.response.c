int func0(char *str)
{
 int i;
 int count;
 int maxcount;

 count = 0;
 maxcount = 0;
 for (i = 0; i < strlen(str); i++)
 {
  if (str[i] == '[')
  {
   count++;
  }
  if (str[i] == ']')
  {
   count--;
  }
  if (count < 0)
  {
   count = 0;
  }
  if (count > maxcount)
  {
   maxcount = count;
  }
  if (count < maxcount - 1)
  {
   return 1;
  }
 }
 return 0;
}