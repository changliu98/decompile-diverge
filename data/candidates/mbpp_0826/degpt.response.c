/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char * func0(int a,int b,int c)

{
  int iVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  int sqc;
  int sqb;
  int sqa;
  int c_local;
  int b_local;
  int a_local;
  char *local_10;
  
  dVar4 = pow((double)a,_DAT_00102008);
  iVar1 = (int)dVar4;
  dVar4 = pow((double)b,_DAT_00102008);
  iVar2 = (int)dVar4;
  dVar4 = pow((double)c,_DAT_00102008);
  iVar3 = (int)dVar4;
  if (((iVar1 == iVar2 + iVar3) || (iVar2 == iVar1 + iVar3)) || (iVar3 == iVar1 + iVar2)) {
    local_10 = "Right-angled Triangle";
  }
  else if (((iVar3 + iVar2 < iVar1) || (iVar1 + iVar3 < iVar2)) || (iVar1 + iVar2 < iVar3)) {
    local_10 = "Obtuse-angled Triangle";
  }
  else {
    local_10 = "Acute-angled Triangle";
  }
  return local_10;
}