int func0(char *str)

{
  size_t sVar1;
  int str_len;
  char *str_local;
  
  sVar1 = strlen(str);
  return ((int)sVar1 * ((int)sVar1 + 1)) / 2;
}