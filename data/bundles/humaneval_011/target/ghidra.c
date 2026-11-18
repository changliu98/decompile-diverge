char * func0(char *a,char *b)

{
  char cVar1;
  size_t sVar2;
  size_t sVar3;
  int local_40;
  int i;
  char *output;
  int min_len;
  int len_b;
  int len_a;
  char *b_local;
  char *a_local;
  char *local_10;
  
  sVar2 = strlen(a);
  sVar3 = strlen(b);
  local_40 = (int)sVar3;
  if ((int)sVar2 < local_40) {
    local_40 = (int)sVar2;
  }
  local_10 = malloc((long)(local_40 + 1));
  if (local_10 == (char *)0x0) {
    local_10 = (char *)0x0;
  }
  else {
    for (i = 0; i < local_40; i = i + 1) {
      cVar1 = '1';
      if (a[i] == b[i]) {
        cVar1 = '0';
      }
      local_10[i] = cVar1;
    }
    local_10[local_40] = '\0';
  }
  return local_10;
}