char * func0(int n)

{
  int iVar1;
  int i_1;
  char *ptr;
  char *out;
  int i;
  int len;
  int n_local;
  char *local_10;
  
  len = 2;
  for (i = 1; i <= n; i = i + 1) {
    iVar1 = snprintf((char *)0x0,0," %d",(ulong)(uint)i);
    len = iVar1 + len;
  }
  local_10 = malloc((long)len);
  if (local_10 == (char *)0x0) {
    local_10 = (char *)0x0;
  }
  else {
    iVar1 = sprintf(local_10,"0");
    ptr = local_10 + iVar1;
    for (i_1 = 1; i_1 <= n; i_1 = i_1 + 1) {
      iVar1 = sprintf(ptr," %d",(ulong)(uint)i_1);
      ptr = ptr + iVar1;
    }
  }
  return local_10;
}