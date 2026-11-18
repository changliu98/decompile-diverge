int memcasecmp(void *vs1,void *vs2,size_t n)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int diff;
  int U2;
  int U1;
  uchar u2;
  uchar u1;
  size_t i;
  char *s2;
  char *s1;
  size_t n_local;
  void *vs2_local;
  void *vs1_local;
  
  i = 0;
  while( true ) {
    if (n <= i) {
      return 0;
    }
    bVar1 = *(byte *)((long)vs2 + i);
    iVar2 = toupper((uint)*(byte *)((long)vs1 + i));
    iVar3 = toupper((uint)bVar1);
    if (iVar2 - iVar3 != 0) break;
    i = i + 1;
  }
  return iVar2 - iVar3;
}