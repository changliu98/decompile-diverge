void func0(char *str, char *out)
{
 int i;
 int length = strlen(str);

 for (i = 0; i < length; i++)
 {
  char w = str[i];

  if (w >= 'a' && w <= 'z')
  {
   w += 'A' - 'a';
  }
  else if (w >= 'A' && w <= 'Z')
  {
   w += 'a' - 'A';
  }

  out[i] = w;
 }

 out[length] = 0;
}