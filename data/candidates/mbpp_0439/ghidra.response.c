int func0(int *L,int size)

{
  int iVar1;
  int i;
  char numStr [20];
  char temp [256];
  int size_local;
  int *L_local;
  
  memset(temp,0,0x100);
  for (i = 0; i < size; i = i + 1) {
    sprintf(numStr,"%d",(ulong)(uint)L[i]);
    strcat(temp,numStr);
  }
  iVar1 = atoi(temp);
  return iVar1;
}