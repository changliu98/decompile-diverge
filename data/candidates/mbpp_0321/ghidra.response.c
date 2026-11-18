char * func0(char *s)

{
  int iVar1;
  size_t sVar2;
  int i_1;
  int i;
  int pos;
  int l;
  char *s_local;
  
  sVar2 = strlen(s);
  i_1 = (int)sVar2;
  pos = 0;
  for (i = 1; i <= i_1; i = i + 1) {
    iVar1 = sprintf(func0::res + pos,"%d",(ulong)(uint)i);
    pos = iVar1 + pos;
  }
  while (i_1 = i_1 + -1, 0 < i_1) {
    iVar1 = sprintf(func0::res + pos,"%d",(ulong)(uint)i_1);
    pos = iVar1 + pos;
  }
  func0::res[pos] = '\0';
  return func0::res;
}