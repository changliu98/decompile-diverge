char * func0(char *str)

{
  size_t sVar1;
  int len;
  char *str_local;
  char *local_10;
  
  sVar1 = strlen(str);
  if (*str == str[(int)sVar1 + -1]) {
    local_10 = "Equal";
  }
  else {
    local_10 = "Not Equal";
  }
  return local_10;
}