char *strcopy(char *dest, char *src)
{
  int i; int j;
  for(i = 0; dest[i]; i++);
  for(j = 0; src[j]; j++);
  for(i = -1; src[++i];);
  if(j > i)
    return "";
  for(; src[i]; i++)
    dest[i] = src[i];
  dest[i] = '\0';
  return dest;
}