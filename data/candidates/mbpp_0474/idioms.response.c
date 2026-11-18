char *func0(char *str, char oldch, char newch)
{
  int i;
  strcpy(str2,str);
  for (i=0; i<strlen(str2); i++)
  {
    if (str2[i]==oldch)
      str2[i]=newch;
  }
  return str2;
}