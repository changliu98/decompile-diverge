char ** func0(int n,char *str,int *count)

{
  size_t sVar1;
  char *token;
  int index;
  int *count_local;
  char *str_local;
  int n_local;
  
  index = 0;
  token = strtok(str," ");
  while (token != (char *)0x0) {
    sVar1 = strlen(token);
    if ((ulong)(long)n < sVar1) {
      func0::word_len[index] = token;
      index = index + 1;
    }
    token = strtok((char *)0x0," ");
  }
  *count = index;
  return func0::word_len;
}