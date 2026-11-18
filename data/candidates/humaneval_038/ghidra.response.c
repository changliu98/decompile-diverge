void func0(char *s,int encode)

{
  char cVar1;
  char cVar2;
  int iVar3;
  size_t sVar4;
  int local_30;
  char temp_1;
  char temp;
  int len;
  int i;
  char x [4];
  int num;
  int l;
  int encode_local;
  char *s_local;
  
  sVar4 = strlen(s);
  iVar3 = (int)sVar4;
  for (i = 0; i < (iVar3 + 2) / 3; i = i + 1) {
    if (iVar3 < i * 3 + 3) {
      local_30 = iVar3 + i * -3;
    }
    else {
      local_30 = 3;
    }
    strncpy(x,s + i * 3,(long)local_30);
    x[local_30] = '\0';
    cVar2 = x[2];
    cVar1 = x[0];
    if (local_30 == 3) {
      if (encode == 0) {
        x[0] = x[1];
        x[1] = x[2];
        x[2] = cVar1;
      }
      else {
        x[2] = x[1];
        x[1] = x[0];
        x[0] = cVar2;
      }
    }
    strncpy(s + i * 3,x,(long)local_30);
  }
  return;
}