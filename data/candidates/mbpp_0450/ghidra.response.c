char ** func0(char **str,int n,int l,int *size)

{
  size_t sVar1;
  int i;
  int count;
  int *size_local;
  int l_local;
  int n_local;
  char **str_local;
  
  count = 0;
  for (i = 0; i < n; i = i + 1) {
    sVar1 = strlen(str[i]);
    if (sVar1 == (long)l) {
      func0::result[count] = str[i];
      count = count + 1;
    }
  }
  *size = count;
  return func0::result;
}