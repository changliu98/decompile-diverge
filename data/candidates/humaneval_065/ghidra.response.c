char * func0(int x,int shift)

{
  char cVar1;
  int iVar2;
  size_t sVar3;
  char temp_1 [50];
  char temp;
  int i;
  int len;
  int shift_local;
  int x_local;
  
  sprintf(func0::xs,"%d",(ulong)(uint)x);
  sVar3 = strlen(func0::xs);
  iVar2 = (int)sVar3;
  if (iVar2 < shift) {
    for (i = 0; i < iVar2 / 2; i = i + 1) {
      cVar1 = func0::xs[i];
      func0::xs[i] = func0::xs[(iVar2 + -1) - i];
      func0::xs[(iVar2 + -1) - i] = cVar1;
    }
  }
  else {
    strcpy(temp_1,func0::xs + ((long)iVar2 - (long)shift));
    temp_1[shift] = '\0';
    strncat(temp_1,func0::xs,(long)(iVar2 - shift));
    strcpy(func0::xs,temp_1);
  }
  return func0::xs;
}