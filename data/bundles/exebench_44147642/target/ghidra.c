void uppercase(int *chptr)

{
  int iVar1;
  int ch;
  int *chptr_local;
  
  iVar1 = *chptr;
  if ((((0x60 < iVar1) && (iVar1 < 0x6a)) || ((0x69 < iVar1 && (iVar1 < 0x73)))) ||
     ((0x72 < iVar1 && (iVar1 < 0x7b)))) {
    *chptr = iVar1 + -0x20;
  }
  return;
}