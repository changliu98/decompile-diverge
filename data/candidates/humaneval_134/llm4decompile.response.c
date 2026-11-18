int func0(char *txt)
{
 int len = strlen(txt);
 if (len == 0)
  return 0;
 if (!isdigit((unsigned char)txt[len - 1]))
  return 0;
 if (len == 1)
  return 1;
 if (!isdigit((unsigned char)txt[len - 2]))
  return 1;
 return 0;
}